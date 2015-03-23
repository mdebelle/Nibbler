#include "GlDisplay.h"
#include <stdexcept>

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
	if (!glfwInit())
		throw std::runtime_error("Failed to initialize GLFW.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_Window = glfwCreateWindow(width * UNIT_SIZE, height * UNIT_SIZE, "Nibbler", NULL, NULL);
	if (!_Window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window.");
	}
	glfwMakeContextCurrent(_Window);
	glewExperimental = true; 
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("Failed to initialize GLEW.");
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
