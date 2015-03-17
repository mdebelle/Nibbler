#include "Pattern.h"

Pattern::Pattern(Point position, Type type) : 
	_Position(position),
	_Size(1, 1),
	_Type(type),
	_Visible(false)
{
	return ;
}

Pattern::Pattern(const Pattern &other) : 
	_Position(other._Position),
	_Size(other._Size),
	_Type(other._Type),
	_Visible(other._Visible)
{
	return ;
}

Pattern			Pattern::operator=(const Pattern &other) 
{
	return (Pattern(other));
}

Pattern::Pattern(Point position, Point size, Type type) :
	_Position(position),
	_Size(size),
	_Type(type),
	_Visible(false)
{
	return ;
}

Pattern::~Pattern()
{
	return ;
}

Point			Pattern::get_Position(void) const
{
	return (_Position);
}

Point			Pattern::get_Size(void) const
{
	return (_Size);
}

Pattern::Type	Pattern::get_Type(void) const
{
	return (_Type);
}

bool			Pattern::get_Visible(void) const
{
	return (_Type);
}

void			Pattern::set_Position(Point position)
{
	_Position = position;
	return ;
}

void			Pattern::set_Visible(bool v)
{
	_Visible = v;
	return ;
}

