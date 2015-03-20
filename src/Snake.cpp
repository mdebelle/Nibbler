#include "Snake.h"

Snake::Snake(int x, int y) :
	_Direction(LEFT)
{
	_Body.push_back(Pattern(Point(x, y), Pattern::body));
	_Body.push_back(Pattern(Point(x + 1, y), Pattern::body));
	_Body.push_back(Pattern(Point(x + 2, y), Pattern::body));
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

void	Snake::moveTo(Direction dir)
{
	if (dir + _Direction != 0)
		_Direction = dir;
	move();
	return ;
}

void	Snake::grow()
{
	Point	pos(_Body.front().get_Position());

	if (_Direction == LEFT)
		pos.x -= 1;
	else if (_Direction == RIGHT)
		pos.x += 1;
	else if (_Direction == UP)
		pos.y -= 1;
	else if (_Direction == DOWN)
		pos.y += 1;
	_Body.insert(_Body.begin(), Pattern(pos, Pattern::body));
	return ;
}

void	Snake::slim()
{
	_Body.pop_back();
	return ;
}

Point	Snake::getPosition() const
{
	return _Body.front().get_Position();
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
