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

void	SfDisplay::drawPattern(int posX, int posY, int sizeX, int sizeY, Pattern::Type type)
{
(void)posX;
(void)posY;
(void)sizeX;
(void)sizeY;
(void)type;
}

void	SfDisplay::drawField()
{

}

void	SfDisplay::display()
{

}

void	SfDisplay::close()
{

}

IDisplay::Key	SfDisplay::getEvent()
{
	return IDisplay::NONE;
}
