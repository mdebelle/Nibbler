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

void	GlDisplay::drawPattern(int posX, int posY, int sizeX, int sizeY, Pattern::Type type)
{
(void)posX;
(void)posY;
(void)sizeX;
(void)sizeY;
(void)type;
}

void	GlDisplay::drawField()
{

}

void	GlDisplay::display()
{

}

void	GlDisplay::close()
{

}

IDisplay::Key	GlDisplay::getEvent()
{
	return IDisplay::NONE;
}
