#include "Snake.h"

Snake::Snake(int x, int y) :
	_AltColor(false),
	_Speed(0),
	_Pts(0),
	_Ate(0),
	_SizeChange(0)
{
	_Body.push_back(Pattern(Point(x, y), Pattern::headL));
	_Body.push_back(Pattern(Point(x + 1, y), Pattern::bodyLR));
	_Body.push_back(Pattern(Point(x + 2, y), Pattern::bodyLR));
	_Body.push_back(Pattern(Point(x + 3, y), Pattern::tailR));

	_SnakeDir[Snake::UP] = &Snake::DirUp;
	_SnakeDir[Snake::DOWN] = &Snake::DirDown;
	_SnakeDir[Snake::LEFT] = &Snake::DirLeft;
	_SnakeDir[Snake::RIGHT] = &Snake::DirRight;

	_Direction.push_back(Direction::LEFT);
	return ;
}

Snake::~Snake()
{
	return ;
}

void	Snake::setStart(std::chrono::steady_clock::time_point& time)
{
	_NextMove = time + std::chrono::milliseconds(_Speed * 10);
}

void	Snake::setAltColor()
{
	_AltColor = true;
	for (Pattern& part : _Body)
		part.set_AltColor();
}

void	Snake::move(int level)
{
	if (std::chrono::steady_clock::now() > _NextMove - std::chrono::milliseconds(level * 10))
	{
		if (_Direction.size() > 1)
			_Direction.erase(_Direction.begin());
		(this->*(_SnakeDir.at(_Direction[0])))();
		if (_AltColor)
		{
			_Body[0].set_AltColor();
			_Body[1].set_AltColor();
		}
		_SizeChange--;
		while (_SizeChange < 0)
		{
			_Body.pop_back();
			_SizeChange++;
		}
		updateTail();
		_Pts++;
		_NextMove += std::chrono::milliseconds(200 - ((_Speed + level) * 10));
	}
	return ;
}

void	Snake::setDirection(Direction dir)
{
	if (dir + _Direction.back() != 0)
		_Direction.push_back(dir);
	return ;
}

void	Snake::DirLeft()
{
	Point	pos(_Body.front().get_Position());

	pos.x -= 1;
	if (_Body[0].get_Position().y == _Body[1].get_Position().y)
		_Body[0].set_Type(Pattern::bodyLR);
	else
		(_Body[0].get_Position().y < _Body[1].get_Position().y) ? _Body[0].set_Type(Pattern::bodyLD) : _Body[0].set_Type(Pattern::bodyLU);

	_Body.insert(_Body.begin(), Pattern(pos, Pattern::headL));
	updateTail();
	return ;
}

void	Snake::DirRight()
{
	Point	pos(_Body.front().get_Position());

	pos.x += 1;

	if (_Body[0].get_Position().y == _Body[1].get_Position().y)
		_Body[0].set_Type(Pattern::bodyLR);
	else
		(_Body[0].get_Position().y < _Body[1].get_Position().y) ? _Body[0].set_Type(Pattern::bodyRD) : _Body[0].set_Type(Pattern::bodyRU);

	_Body.insert(_Body.begin(), Pattern(pos, Pattern::headR));
	updateTail();
	return ;
}

void	Snake::DirUp()
{
	Point	pos(_Body.front().get_Position());

	pos.y -= 1;

	if (_Body[0].get_Position().x == _Body[1].get_Position().x)
		_Body[0].set_Type(Pattern::bodyUD);
	else
		(_Body[0].get_Position().x < _Body[1].get_Position().x) ? _Body[0].set_Type(Pattern::bodyRU) : _Body[0].set_Type(Pattern::bodyLU);

	_Body.insert(_Body.begin(), Pattern(pos, Pattern::headU));
	updateTail();
	return ;
}

void	Snake::DirDown()
{
	Point	pos(_Body.front().get_Position());

	pos.y += 1;

	if (_Body[0].get_Position().x == _Body[1].get_Position().x)
		_Body[0].set_Type(Pattern::bodyUD);
	else
		(_Body[0].get_Position().x < _Body[1].get_Position().x) ? _Body[0].set_Type(Pattern::bodyRD) : _Body[0].set_Type(Pattern::bodyLD);

	_Body.insert(_Body.begin(), Pattern(pos, Pattern::headD));
	updateTail();
	return ;
}

void	Snake::updateTail()
{
	const Pattern& prev = _Body[_Body.size() - 2];

	if (_Body.back().get_Position().x < prev.get_Position().x)
		_Body.back().set_Type(Pattern::tailL);
	else if (_Body.back().get_Position().x > prev.get_Position().x)
		_Body.back().set_Type(Pattern::tailR);
	else if (_Body.back().get_Position().y < prev.get_Position().y)
		_Body.back().set_Type(Pattern::tailU);
	else
		_Body.back().set_Type(Pattern::tailD);

	if (_AltColor)
		_Body.back().set_AltColor();
}

void	Snake::grow()
{
	_SizeChange++;
	return ;
}

void	Snake::scissors()
{
	_SizeChange -= _Body.size() / 2;
}

Point	Snake::getPosition() const
{
	return _Body.front().get_Position();
}

int		Snake::getSize() const
{
	return _Body.size();
}

const std::vector<Pattern>& Snake::getBody() const
{
	return _Body;
}

bool	Snake::isOnBody(Point point) const
{
	for (const Pattern& body_part : _Body)
		if (body_part.get_Position() == point)
			return 1;
	return 0;
}

bool	Snake::eatsItself() const
{
	std::vector<Pattern>::const_iterator it = _Body.begin();
	for (++it; it != _Body.end(); ++it)
		if (it->get_Position() == _Body.front().get_Position())
			return 1;
	return 0;
}

int		Snake::getSpeed() const
{
	return _Speed;
}

int		Snake::getAte() const
{
	return _Ate;
}

int		Snake::getPts() const
{
	return _Pts;
}

void	Snake::setPts(int pts)
{
	_Pts = pts;
}

void	Snake::speedUp()
{
	if (_Speed < 10)
		_Speed++;
}

void	Snake::speedDown()
{
	if (_Speed > 0)
		_Speed--;
}

void	Snake::eat(Pattern::Type type)
{
	_Ate++;
	switch (type)
	{
		case Pattern::fruit2:
			speedUp();
			break;
		case Pattern::fruit3:
			speedDown();
			break;
		case Pattern::fruit4:
			scissors();
			break;
		default:
			break;
	}
	grow();
}
