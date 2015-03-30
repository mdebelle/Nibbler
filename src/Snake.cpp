#include "Snake.h"

Snake::Snake(int x, int y) :
	_Direction(LEFT),
	_DirectionFrom(RIGHT)
{
	_Body.push_back(Pattern(Point(x, y), Pattern::headL));
	_Body.push_back(Pattern(Point(x + 1, y), Pattern::bodyLR));
	_Body.push_back(Pattern(Point(x + 2, y), Pattern::bodyLR));
	_Body.push_back(Pattern(Point(x + 3, y), Pattern::tailR));

	_SnakeDir[Snake::UP] = &Snake::DirUp;
	_SnakeDir[Snake::DOWN] = &Snake::DirDown;
	_SnakeDir[Snake::LEFT] = &Snake::DirLeft;
	_SnakeDir[Snake::RIGHT] = &Snake::DirRight;

	return ;
}

Snake::~Snake()
{
	return ;
}

void	Snake::move()
{
	grow();
	slim();
	return ;
}

void	Snake::setDirection(Direction dir)
{
	if (dir + _Direction != 0)
		_Direction = dir;
	return ;
}

Snake::Direction	Snake::getDirection() const
{
	return _Direction;
}

void	Snake::grow()
{
	(this->*(_SnakeDir.at(_Direction)))();
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
//	else if (_Body.end()->get_Position().y > prev.get_Position().y)
	else
		_Body.back().set_Type(Pattern::tailD);
}

void	Snake::scissors()
{
	for (unsigned int i = _Body.size() / 2; i > 0; i--)
		_Body.pop_back();
	updateTail();
	return ;
}

void	Snake::slim()
{
	_Body.pop_back();
	updateTail();
	return ;
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
	for (it++; it != _Body.end(); it++)
		if (it->get_Position() == _Body.front().get_Position())
			return 1;
	return 0;
}

