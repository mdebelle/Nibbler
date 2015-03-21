#include "NcDisplay.h"
#include <ncurses.h>

NcDisplay::NcDisplay() : _SizeX(0), _SizeY(0)
{
	_Key_map[0x1b5b43] = IDisplay::RIGHT;
	_Key_map[0x1b5b44] = IDisplay::LEFT;
	_Key_map[0x1b5b42] = IDisplay::DOWN;
	_Key_map[0x1b5b41] = IDisplay::UP;
	_Key_map[' '] = IDisplay::SPACE;
	_Key_map[27] = IDisplay::ESC;
	_Key_map['1'] = IDisplay::ONE;
	_Key_map['2'] = IDisplay::TWO;
	_Key_map['3'] = IDisplay::THREE;
	return ;
}

NcDisplay::~NcDisplay()
{
	return ;
}

void	NcDisplay::init(int width, int height)
{
	_SizeX = width;
	_SizeY = height;
	initscr();
	start_color();
	noecho();
	curs_set(FALSE);
	cbreak();
	timeout(1);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	init_pair(3, COLOR_BLACK, COLOR_RED);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
}

void	NcDisplay::drawPattern(int posX, int posY, int sizeX, int sizeY, Pattern::Type type)
{
	int	colo = 1;

	if (type == Pattern::body)
		colo = 2;
	else if (type == Pattern::fruit)
		colo = 3;
	else if (type == Pattern::head)
		colo = 4;
	attron(COLOR_PAIR(colo));
	for (int j = 1; j <= sizeY; j++)
	{
		for (int i = 1; i <= sizeX; i++)
		{
			move(posY + j, (posX + i) * 2);
			addch(' ');
			addch(' ');
		}
	}
	attroff(COLOR_PAIR(colo));
}

void	NcDisplay::drawField()
{
	clear();
	attron(COLOR_PAIR(1));
	move(0, 0);
	for (int i = 0; i < _SizeX * 2 + 4; i++)
		addch(' ');
	for (int i = 1; i <= _SizeY; i++)
	{
		move(i, 0);
		addch(' ');
		addch(' ');
		move(i, _SizeX * 2 + 2);
		addch(' ');
		addch(' ');
	}
	move(_SizeY + 1, 0);
	for (int i = 0; i < _SizeX * 2 + 4; i++)
		addch(' ');
	attroff(COLOR_PAIR(1));
}

void	NcDisplay::display()
{
	refresh();
}

void	NcDisplay::close()
{
	endwin();
}

IDisplay::Key	NcDisplay::getEvent()
{
	IDisplay::Key	key = IDisplay::NONE;
	int				code, tmp;

	code = getch();
	if (code == 27)
	{
		code = 27;
		while ((tmp = getch()) != ERR)
		{
			code <<= 8;
			code += tmp;
		}
	}
	try {
		key = _Key_map.at(code);
	}
	catch (std::exception& ex) {
		key = IDisplay::NONE;
	}
	return key;
}
