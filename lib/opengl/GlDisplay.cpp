#include "GlDisplay.h"
#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>
#include "loaders.h"

int GlDisplay::_LastKey = 0;

static void
keycallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		GlDisplay::_LastKey = key;
	(void)window;
	(void)scancode;
	(void)action;
	(void)mods;
}

GlDisplay::GlDisplay() :
	_Window(nullptr),
	_Width(0),
	_Height(0)
{
	_Key_map[GLFW_KEY_SPACE] = IDisplay::SPACE;
	_Key_map[GLFW_KEY_ESCAPE] = IDisplay::ESC;
	_Key_map[GLFW_KEY_DOWN] = IDisplay::DOWN;
	_Key_map[GLFW_KEY_UP] = IDisplay::UP;
	_Key_map[GLFW_KEY_LEFT] = IDisplay::LEFT;
	_Key_map[GLFW_KEY_RIGHT] = IDisplay::RIGHT;
	_Key_map[GLFW_KEY_W] = IDisplay::W;
	_Key_map[GLFW_KEY_A] = IDisplay::A;
	_Key_map[GLFW_KEY_S] = IDisplay::S;
	_Key_map[GLFW_KEY_D] = IDisplay::D;
	_Key_map[GLFW_KEY_M] = IDisplay::M;
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

	_Width = 2.0f / width;
	_Height = 2.0f / (height + 4);
	_Window = glfwCreateWindow(width * UNIT_SIZE, (height + 4) * UNIT_SIZE, "Nibbler", NULL, NULL);
	if (!_Window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window.");
	}
	glfwSetKeyCallback(_Window, &keycallback);
	glfwMakeContextCurrent(_Window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("Failed to initialize GLEW.");

	try { _Text.init("lib/opengl/text.dds"); }
	catch (std::exception& ex) { throw; }

	glGenVertexArrays(1, &_VertexArrayID);
	glBindVertexArray(_VertexArrayID);

	try { _ProgramID = loadShaders("vertex.glsl", "fragment.glsl"); }
	catch (std::exception& ex) { throw; }

	glGenBuffers(1, &_VertexBuffer);
	glGenBuffers(1, &_ColorBuffer);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void	GlDisplay::drawPattern(int posX, int posY, Pattern::Type type)
{
	_Vertices.insert(_Vertices.end(), {
		-1 + (posX * _Width)		, 1 - (posY * _Height), 0.0f,
		-1 + ((posX + 1) * _Width)	, 1 - (posY * _Height), 0.0f,
		-1 + (posX * _Width)		, 1 - ((posY + 1) * _Height), 0.0f,
		-1 + ((posX + 1) * _Width)	, 1 - (posY * _Height), 0.0f,
		-1 + (posX * _Width)		, 1 - ((posY + 1) * _Height), 0.0f,
		-1 + ((posX + 1) * _Width)	, 1 - ((posY + 1) * _Height), 0.0f
	});

	float c[3] = { 0.0f, 0.0f, 0.0f };
	if (type == Pattern::bodyLR || type == Pattern::bodyUD || type == Pattern::bodyLU ||
		type == Pattern::bodyLD || type == Pattern::bodyRD || type == Pattern::bodyRU ||
		type == Pattern::tailD || type == Pattern::tailU || type == Pattern::tailR || type == Pattern::tailL
	)
		c[1] = 0.4f;
	else if (type == Pattern::bodyLR2 || type == Pattern::bodyUD2 || type == Pattern::bodyLU2 ||
		type == Pattern::bodyLD2 || type == Pattern::bodyRD2 || type == Pattern::bodyRU2 ||
		type == Pattern::tailD2 || type == Pattern::tailU2 || type == Pattern::tailR2 || type == Pattern::tailL2
	)
	{
		c[1] = 0.4f;
		c[0] = 0.5f;
	}
	else if (type == Pattern::headL || type == Pattern::headR || type == Pattern::headU ||
			 type == Pattern::headD || type == Pattern::headL2 || type == Pattern::headR2 ||
			 type == Pattern::headU2 || type == Pattern::headD2
	) {
		c[0] = 0.9f;
		c[1] = 0.9f;
	}
	else if (type == Pattern::fruit1)
		c[0] = 1.0f;
	else if (type == Pattern::fruit2)
	{
		c[0] = 1.0f;
		c[2] = 1.0f;
	}
	else if (type == Pattern::fruit3)
	{
		c[1] = 1.0f;
		c[2] = 1.0f;
	}
	else if (type == Pattern::fruit4)
		c[2] = 1.0f;
	for (int i = 0; i < 6; i++)
		_Colors.insert(_Colors.end(), { c[0], c[1], c[2] });
}

void	GlDisplay::drawMenu(bool multi, bool sound)
{
	glClear( GL_COLOR_BUFFER_BIT );
	_Vertices.clear();
	_Colors.clear();
	_Text.print("NIBBLER", -1.0f + _Width, 1.0f - _Height * 4, _Height * 3);
	std::string str("Multiplayer: ");
	str += multi ? "enabled" : "disabled";
	_Text.print(str, -1.0f + _Width, 1.0f - _Height * 7, _Height);
	_Text.print("Press 'M' to switch!", -1.0f + _Width, 1.0f - _Height * 8.2, _Height);
	str = "Sound: ";
	str += sound ? "enabled" : "disabled";
	_Text.print(str, -1.0f + _Width, 1.0f - _Height * 10, _Height);
	_Text.print("Press 'S' to switch!", -1.0f + _Width, 1.0f - _Height * 11.2, _Height);
	_Text.print("Press space to start.", -1.0f + _Width, 1.0f - _Height * 13, _Height);
	_Text.print("Press escape to quit.", -1.0f + _Width, 1.0f - _Height * 14.2, _Height);
}

void	GlDisplay::drawField()
{
	_Vertices.clear();
	_Colors.clear();

	glClear( GL_COLOR_BUFFER_BIT );
	_Vertices.insert(_Vertices.end(), {
		-1.0f, 1.0f						, 0.0f,
		-1.0f, -1.0f + (_Height * 4)	, 0.0f,
		1.0f , -1.0f + (_Height * 4)	, 0.0f,
		1.0f , -1.0f + (_Height * 4)	, 0.0f,
		-1.0f, 1.0f						, 0.0f,
		1.0f , 1.0f						, 0.0f
	});
	for (int i = 0; i < 18; i++)
		_Colors.push_back(1.0f);
}


void	GlDisplay::drawScoring(int pts, int player, int level, bool multi)
{
	if (multi == true)
	{
		if (player == 1)
		{
			_Text.print(std::string("Player 1: ") + std::to_string(pts), -1.0f + _Width, -1.0f + _Height * 2.2, _Height);
			_Text.print(std::string("Level   : ") + std::to_string(level), -1.0f + _Width, -1.0f + _Height * 1, _Height);
		}
		else if (player == 2)
			_Text.print(std::string("Player 2: ") + std::to_string(pts), _Width, -1.0f + _Height * 2.2, _Height);
	}
	else
	{
		_Text.print(std::string("Score: ") + std::to_string(pts), -1.0f + _Width, -1.0f + _Height * 2.2, _Height);
		_Text.print(std::string("Level: ") + std::to_string(level), -1.0f + _Width, -1.0f + _Height * 1, _Height);
	}
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
	if (_LastKey)
		try {
			IDisplay::Key key = _Key_map.at(_LastKey);
			_LastKey = 0;
			return key;
		}
		catch(std::exception& ex) { _LastKey = 0; }
	return IDisplay::NONE;
}
