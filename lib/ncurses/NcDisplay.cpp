#include "NcDisplay.h"
#include <sys/ioctl.h>

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

	_Charset[Pattern::bodyLU] = 106|A_ALTCHARSET;
	_Charset[Pattern::bodyLD] = 107|A_ALTCHARSET;
	_Charset[Pattern::bodyRU] = 109|A_ALTCHARSET;
	_Charset[Pattern::bodyRD] = 108|A_ALTCHARSET;
	_Charset[Pattern::bodyLR] = 113|A_ALTCHARSET;
	_Charset[Pattern::bodyUD] = 120|A_ALTCHARSET;
	_Charset[Pattern::fruit1] = '1';
	_Charset[Pattern::fruit2] = '2';
	_Charset[Pattern::fruit3] = '3';
	_Charset[Pattern::fruit4] = '4';
	_Charset[Pattern::headL] = '<';
	_Charset[Pattern::headR] = '>';
	_Charset[Pattern::headU] = '^';
	_Charset[Pattern::headD] = 'v';
	_Charset[Pattern::wall] = ' ';

	return ;
}

NcDisplay::~NcDisplay()
{
	return ;
}

void	NcDisplay::init(int width, int height)
{
	struct winsize size;
	if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
		throw std::runtime_error("Can't get terminal size.");
	if (height + 2 > size.ws_row || width * 2 + 4 > size.ws_col)
		throw std::runtime_error("Size is too big for the terminal size.");

	_SizeX = width;
	_SizeY = height;
	initscr();
	if (!has_colors())
	{
		endwin();
		throw std::runtime_error("Terminal does not support colors.");
	}
	start_color();
	noecho();
	curs_set(FALSE);
	cbreak();
	timeout(1);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_RED);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
}

void	NcDisplay::drawMenu()
{
	clear();
	int j;

	j = 0;
	attron(COLOR_PAIR(1));
	for (int i = 0; i < 15; i++)
	{
		move(i, 0);
		for (int j = 0; j < _SizeX + 2; j++)
			addch(' ');
		j = 0;
	}

	move(0, 0);
	mvwprintw(stdscr, 0, 0, "%s ", "                __");
	move(1, 0);
	mvwprintw(stdscr, 1, 0, "%s ", "     ______    /* >-<");
	move(2, 0);
	mvwprintw(stdscr, 2, 0, "%s ", " ___/ ____ \\__/ /");
	move(3, 0);
	mvwprintw(stdscr, 3, 0, "%s ", "<____/    \\____/");
	move(4, 0);
	mvwprintw(stdscr, 4, 0, "%s ", "");

	attroff(COLOR_PAIR(1));
	return ;
}

void	NcDisplay::drawPattern(int posX, int posY, int sizeX, int sizeY, Pattern::Type type)
{
	int	colo = 1;

	if (type == Pattern::bodyLU || type == Pattern::bodyLD || type == Pattern::bodyRU ||
		type == Pattern::bodyRD || type == Pattern::bodyLR || type == Pattern::bodyUD
	)
		colo = 2;
	else if (type == Pattern::fruit1 || type == Pattern::fruit2 || type == Pattern::fruit3 || type == Pattern::fruit4)
		colo = 3;
	else if (type == Pattern::headL || type == Pattern::headR || type == Pattern::headU || type == Pattern::headD)
		colo = 4;

	attron(COLOR_PAIR(colo));
	for (int j = 1; j <= sizeY; j++)
	{
		for (int i = 1; i <= sizeX; i++)
		{
			move(posY + j, (posX + i));
			addch(_Charset.at(type));
		}
	}
	attroff(COLOR_PAIR(colo));
}

void	NcDisplay::drawScoring(int pts, int level, int speed)
{
	attron(COLOR_PAIR(1));
	move(_SizeY + 2, 0);
	for (int i = 0; i < _SizeX + 2; i++)
			addch(' ');
	mvwprintw(stdscr, _SizeY + 2, 0, "%s %6d %2d %2d", "Scoring", pts, level, speed);
	move(_SizeY + 3, 0);
	for (int i = 0; i < _SizeX + 2; i++)
			addch(' ');
	mvwprintw(stdscr, _SizeY + 3, 0, "%s %2d %s %2d", "Level:", level, "Speed:", speed);
	attroff(COLOR_PAIR(1));


	return ;
}

void	NcDisplay::drawField()
{
	clear();
	attron(COLOR_PAIR(1));
	move(0, 0);
	for (int i = 0; i < _SizeX + 2; i++)
		addch(97 | A_ALTCHARSET);
	for (int i = 1; i <= _SizeY; i++)
	{
		move(i, 0);
		addch(97 | A_ALTCHARSET);
		move(i, _SizeX + 1);
		addch(97 | A_ALTCHARSET);
	}
	move(_SizeY + 1, 0);
	for (int i = 0; i < _SizeX + 2; i++)
		addch(97 | A_ALTCHARSET);

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
