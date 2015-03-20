#include "NcDisplay.h"

NcDisplay::NcDisplay()
{
	return ;
}

NcDisplay::~NcDisplay()
{
	return ;
}

void	NcDisplay::init(int width, int height)
{
(void)width;
(void)height;
}

void	NcDisplay::refresh()
{

}

void	NcDisplay::close()
{

}

IDisplay::Key	NcDisplay::getEvent()
{
	return IDisplay::NONE;
}
