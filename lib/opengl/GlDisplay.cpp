#include "GlDisplay.h"
#include <openGL/gl.h>
#include <openGL/glu.h>	
#include <GLUT/glut.h>



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
//	char	argv[1][10] = { "./Nibbler" };
//	int		argc = 1;


    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width, height); 
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("Tutorial 01");
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutMainLoop();
	glClear(GL_COLOR_BUFFER_BIT); 
	glutSwapBuffers();

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
