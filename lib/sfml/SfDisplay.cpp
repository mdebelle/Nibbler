#include "SfDisplay.h"

SfDisplay::SfDisplay()
{
	return ;
}

SfDisplay::~SfDisplay()
{
	return ;
}

void	SfDisplay::init(int width, int height)
{
(void)width;
(void)height;
}

void	SfDisplay::refresh()
{

}

void	SfDisplay::close()
{

}

IDisplay::Key	SfDisplay::getEvent()
{
	return IDisplay::NONE;
}
