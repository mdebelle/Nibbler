#include "Pattern.h"

Pattern::Pattern(Point position, Type type) : 
	_Position(position),
	_Type(type)
{
	_Size.x = 1;
	_Size.y = 1;
	return ;
}

Pattern::Pattern(Point position, Point size, Type type) :
	_Position(position),
	_Size(size),
	_Type(type)
{
	return ;
}

Pattern::~Pattern()
{
	return ;
}

Point	Pattern::get_Position(void) const
{
	return (_Position);
}

Point	Pattern::get_Size(void) const
{
	return (_Size);
}

Type	Pattern::get_Type(void) const
{
	return (_Type);
}

void	Pattern::set_Position(Point position)
{
	_Position = position;
	return ;
}

