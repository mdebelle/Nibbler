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

	try {
		_ProgramID = loadShader("lib/opengl/shader/vertex.glsl", "lib/opengl/shader/fragment.glsl");
	}
	catch (std::exception& ex) { throw ex; }
	glGenBuffers(1, &_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

GLuint	GlDisplay::loadShader(const char* vertex_file_path, const char* fragment_file_path)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(!VertexShaderStream.is_open())
		throw std::runtime_error(std::string("Impossible to open ") + vertex_file_path + ".");
	std::string Line = "";
	while(getline(VertexShaderStream, Line))
		VertexShaderCode += "\n" + Line;
	VertexShaderStream.close();

	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open())
	{
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		throw std::runtime_error(&VertexShaderErrorMessage[0]);
	}

	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		throw std::runtime_error(&FragmentShaderErrorMessage[0]);
	}

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		throw std::runtime_error(&ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return ProgramID;
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
	glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);

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
