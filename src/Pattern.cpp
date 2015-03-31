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

void			Pattern::set_AltColor()
{
	if (_Type == bodyLU)
		_Type = bodyLU2;
	else if (_Type == bodyRU)
		_Type = bodyRU2;
	else if (_Type == bodyRD)
		_Type = bodyRD2;
	else if (_Type == bodyLD)
		_Type = bodyLD2;
	else if (_Type == bodyLR)
		_Type = bodyLR2;
	else if (_Type == bodyUD)
		_Type = bodyUD2;
	else if (_Type == headU)
		_Type = headU2;
	else if (_Type == headD)
		_Type = headD2;
	else if (_Type == headL)
		_Type = headL2;
	else if (_Type == headR)
		_Type = headR2;
	else if (_Type == tailU)
		_Type = tailU2;
	else if (_Type == tailD)
		_Type = tailD2;
	else if (_Type == tailL)
		_Type = tailL2;
	else if (_Type == tailR)
		_Type = tailR2;
}
