#include "GlDisplay.h"

GlDisplay::GlDisplay()
{
	return ;
}

GlDisplay::~GlDisplay()
{
	return ;
}

void	GlDisplay::init(int width, int height)
{
(void)width;
(void)height;
}

void	GlDisplay::refresh()
{

}

void	GlDisplay::close()
{

}

IDisplay::Key	GlDisplay::getEvent()
{
	return IDisplay::NONE;
}
