#include "Area.h"

Area::Area(Point size) :
	_Size(size)
{
	return ;
}

Area::~Area()
{
	return ;
}

int			Area::get_Width() const
{
	return _Size.x;
}

int			Area::get_Height() const
{
	return _Size.y;
}

Point		Area::get_Size() const
{
	return _Size;
}

