#include "Snake.h"

Snake::Snake(int x, int y) :
	_Direction(LEFT)
{
	_Body.push_back(Pattern(Point(x, y), body));
	_Body.push_back(Pattern(Point(x + 1, y), body));
	_Body.push_back(Pattern(Point(x + 2, y), body));
	return ;
}

Snake::~Snake()
{
	return ;
}

void Snake::move()
{
	grow();
	slim();
	return ;
}

void Snake::moveTo(Direction dir)
{
	if (dir + _Direction != 0)
		_Direction = dir;
	move();
	return ;
}

void Snake::grow()
{
	Point pos;

	pos.x = _Body.front().get_Position().x;
	pos.y = _Body.front().get_Position().y;
	if (_direction == LEFT)
		pos.x -= 1;
	else if (_direction == RIGHT)
		pos.x += 1;
	else if (_direction == UP)
		pos.y -= 1;
	else if (_direction == DOWN)
		pos.y += 1;
	_Body.insert(_Body.begin(), Pattern(pos, body));
	return ;
}

void	Snake::slim()
{
	_Body.pop_back();
	return ;
}