#include "GlDisplay.h"
#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>

GlDisplay::GlDisplay() :
	g_vertex_buffer_data {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	}
{
	_Key_map[GLFW_KEY_SPACE] = IDisplay::SPACE;
	_Key_map[GLFW_KEY_ESCAPE] = IDisplay::ESC;
	_Key_map[GLFW_KEY_DOWN] = IDisplay::DOWN;
	_Key_map[GLFW_KEY_UP] = IDisplay::UP;
	_Key_map[GLFW_KEY_LEFT] = IDisplay::LEFT;
	_Key_map[GLFW_KEY_RIGHT] = IDisplay::RIGHT;
	_Key_map[GLFW_KEY_1] = IDisplay::ONE;
	_Key_map[GLFW_KEY_2] = IDisplay::TWO;
	_Key_map[GLFW_KEY_3] = IDisplay::THREE;
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

	glGenVertexArrays(1, &_VertexArrayID);
	glBindVertexArray(_VertexArrayID);

	_ProgramID = glCreateProgram();
	try {
		loadShader("lib/opengl/shader/vertex.glsl");
		loadShader("lib/opengl/shader/fragment.glsl");
	}
	catch (std::exception& ex) { throw ex; }
	glLinkProgram(_ProgramID);

	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(_ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(_ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(_ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		throw std::runtime_error(&ProgramErrorMessage[0]);
	}

	glGenBuffers(1, &_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void	GlDisplay::loadShader(const char* file_path)
{
	GLuint shaderID = glCreateShader(GL_VERTEX_SHADER);

	std::string shaderCode;
	std::ifstream shaderStream(file_path, std::ios::in);
	if(!shaderStream.is_open())
		throw std::runtime_error(std::string("Impossible to open ") + file_path + ".");
	std::string line = "";
	while(getline(shaderStream, line))
		shaderCode += "\n" + line;
	shaderStream.close();

	GLint Result = GL_FALSE;
	int InfoLogLength;

	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer , NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> errorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &errorMessage[0]);
		throw std::runtime_error(&errorMessage[0]);
	}

	glAttachShader(_ProgramID, shaderID);
	glDeleteShader(shaderID);
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
	glClear( GL_COLOR_BUFFER_BIT );
}

void	GlDisplay::drawScoring(int pts)
{
	(void)pts;
	return ;
}

void	GlDisplay::display()
{
	glUseProgram(_ProgramID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	glfwSwapBuffers(_Window);
}

void	GlDisplay::close()
{
	glDeleteBuffers(1, &_VertexBuffer);
	glDeleteVertexArrays(1, &_VertexArrayID);
	glDeleteProgram(_ProgramID);
	glfwTerminate();
}

IDisplay::Key	GlDisplay::getEvent()
{
	glfwPollEvents();
	for (auto key : _Key_map)
	{
		if (glfwGetKey(_Window, key.first) == GLFW_PRESS)
			return key.second;
	}
	return IDisplay::NONE;
}
