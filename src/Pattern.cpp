#include "Pattern.h"

Pattern::Pattern(Point position, Type type) : 
	_Position(position),
	_Type(type),
	_Visible(false)
{
	return ;
}

Pattern::Pattern(const Pattern &other) : 
	_Position(other._Position),
	_Type(other._Type),
	_Visible(other._Visible)
{
	return ;
}

Pattern&		Pattern::operator=(const Pattern &other) 
{
	_Position = other._Position;
	_Type = other._Type;
	_Visible = other._Visible;
	
	return *this;
}

Pattern::~Pattern()
{
	return ;
}

Point			Pattern::get_Position(void) const
{
	return (_Position);
}

Pattern::Type	Pattern::get_Type(void) const
{
	return (_Type);
}

bool			Pattern::get_Visible(void) const
{
	return (_Visible);
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


void			Pattern::set_Type(Type t)
{
	_Type = t;
	return ;
}
