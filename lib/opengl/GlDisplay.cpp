#include "GlDisplay.h"
#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>

GlDisplay::GlDisplay()
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

	_Width = width * UNIT_SIZE;
	_Height = height * UNIT_SIZE;
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
		loadShader("lib/opengl/shader/vertex.glsl", GL_VERTEX_SHADER);
		loadShader("lib/opengl/shader/fragment.glsl", GL_FRAGMENT_SHADER);
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
	glGenBuffers(1, &_ColorBuffer);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void	GlDisplay::loadShader(const char* file_path, GLenum shaderType)
{
	GLuint shaderID = glCreateShader(shaderType);

	std::string shaderCode;
	std::ifstream shaderStream(file_path, std::ios::in);
	if (!shaderStream.is_open())
		throw std::runtime_error(std::string("Impossible to open ") + file_path + ".");
	std::string line = "";
	while (getline(shaderStream, line))
		shaderCode += "\n" + line;
	shaderStream.close();

	GLint Result = GL_FALSE;
	int InfoLogLength;

	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer , NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
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
	float	sqrt_size = 2 / (_Width / UNIT_SIZE);

	_Vertices.insert(_Vertices.end(), {
		-1 + (posX * sqrt_size), 1 - (posY * sqrt_size), 0.0f,
		-1 + ((posX + sizeX) * sqrt_size), 1 - (posY * sqrt_size), 0.0f,
		-1 + (posX * sqrt_size), 1 - ((posY + sizeY) * sqrt_size), 0.0f,
		-1 + ((posX + sizeX) * sqrt_size), 1 - (posY * sqrt_size), 0.0f,
		-1 + (posX * sqrt_size), 1 - ((posY + sizeY) * sqrt_size), 0.0f,
		-1 + ((posX + sizeX) * sqrt_size), 1 - ((posY + sizeY) * sqrt_size), 0.0f
	});
 
	float c[3] = { 0.0f, 0.0f, 0.0f };
	if (type == Pattern::bodyLR || type == Pattern::bodyUD || type == Pattern::bodyLU ||
		type == Pattern::bodyLD || type == Pattern::bodyRD || type == Pattern::bodyRU
	)
		c[1] = 1.0f;
	else if (type == Pattern::headL || type == Pattern::headR || type == Pattern::headU || type == Pattern::headD)
	{
		c[0] = 1.0f;
		c[1] = 1.0f;
	}
	else if (type == Pattern::fruit1 || type == Pattern::fruit2 || type == Pattern::fruit3 || type == Pattern::fruit4)
		c[0] = 1.0f;
	else
	{
		c[0] = 1.0f;
		c[1] = 1.0f;
		c[2] = 1.0f;
	}
	for (int i = 0; i < 6; i++)
		_Colors.insert(_Colors.end(), { c[0], c[1], c[2] });
}

void	GlDisplay::drawMenu()
{

}

void	GlDisplay::drawField()
{
	glClear( GL_COLOR_BUFFER_BIT );
	_Vertices.clear();
	_Colors.clear();
}

void	GlDisplay::drawScoring(int pts, int level, int speed)
{
	(void)pts;
	(void)level;
	(void)speed;
	return ;
}

void	GlDisplay::display()
{
	glUseProgram(_ProgramID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _Vertices.size(), &_Vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _ColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _Colors.size(), &_Colors[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, _Vertices.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glfwSwapBuffers(_Window);
}

void	GlDisplay::close()
{
	glDeleteBuffers(1, &_VertexBuffer);
	glDeleteBuffers(1, &_ColorBuffer);
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
