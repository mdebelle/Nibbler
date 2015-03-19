#include "tools.h"

Point::Point(int px, int py)
{
	x = px;
	y = py;
	return ;
}

Point::Point(const Point& other)
{
	x = other.x;
	y = other.y;
	return ;
}

Point Point::operator=(const Point& other)
{
	return (Point(other));
}

Point::~Point()
{
	return ;
}

bool	operator==(Point pl, Point pr)
{
	return pl.x == pr.x && pl.y == pr.y;
}