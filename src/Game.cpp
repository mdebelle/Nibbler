#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "DisplayFactory.h"

Game::Game(int x, int y, bool multiplayer) :
	_Fruit(Point(0, 0), Pattern::fruit1),
	_Snake((x / 2) - 2, y / 2),
	_Snake2((x / 2) - 2, y / 2 - 2),
	_Area(Point(x, y)),
	_Display(nullptr),
	_IsRunning(false),
	_IsPaused(false),
	_Multi(multiplayer),
	_Level(1),
	_Speed(1),
	_Pts(0),
	_Ate(0)
{
	_Snake2.setAltColor();
	_Key_map[IDisplay::ESC] = &Game::KEsc;
	_Key_map[IDisplay::SPACE] = &Game::KSpace;
	_Key_map[IDisplay::UP] = &Game::KUp;
	_Key_map[IDisplay::RIGHT] = &Game::KRight;
	_Key_map[IDisplay::LEFT] = &Game::KLeft;
	_Key_map[IDisplay::DOWN] = &Game::KDown;
	_Key_map[IDisplay::A] = &Game::KA;
	_Key_map[IDisplay::W] = &Game::KW;
	_Key_map[IDisplay::S] = &Game::KS;
	_Key_map[IDisplay::D] = &Game::KD;
	_Key_map[IDisplay::ONE] = &Game::KOne;
	_Key_map[IDisplay::TWO] = &Game::KTwo;
	_Key_map[IDisplay::THREE] = &Game::KThree;
	try {
		DisplayFactory::load(_Display, 1);
		_Display->init(x, y);
	}
	catch (std::exception& ex) {
		std::cerr << "Error during initialization: " << ex.what() << std::endl;
		exit(-1);
	}
	std::srand(std::time(nullptr));
	popFruit();
	return ;
}

Game::~Game()
{
	_Display->close();
	return ;
}

void	Game::launch()
{
	_IsRunning = true;

	menu();
 
 	sleep(2);
	while (_IsRunning)
	{
		display();
		usleep(200000 - ((_Level - 1 + _Speed) * 10000));
		listen();
		if (!_IsPaused)
			update();
	}
}


void	Game::listen()
{
	IDisplay::Key key = _Display->getEvent();

	if (key != IDisplay::NONE)
		(this->*(_Key_map.at(key)))();
	return ;
}

void	Game::KLeft()
{
	if (!_IsPaused)
		_Snake.setDirection(Snake::LEFT);
	return ;
}

void	Game::KRight()
{
	if (!_IsPaused)
		_Snake.setDirection(Snake::RIGHT);
	return ;
}

void	Game::KUp()
{
	if (!_IsPaused)
		_Snake.setDirection(Snake::UP);
	return ;
}

void	Game::KDown()
{
	if (!_IsPaused)
		_Snake.setDirection(Snake::DOWN);
	return ;
}

void	Game::KA()
{
	if (!_IsPaused)
		_Snake2.setDirection(Snake::LEFT);
	return ;
}

void	Game::KD()
{
	if (!_IsPaused)
		_Snake2.setDirection(Snake::RIGHT);
	return ;
}

void	Game::KW()
{
	if (!_IsPaused)
		_Snake2.setDirection(Snake::UP);
	return ;
}

void	Game::KS()
{
	if (!_IsPaused)
		_Snake2.setDirection(Snake::DOWN);
	return ;
}

void	Game::KEsc()
{
	_IsRunning = false;
	return ;
}

void	Game::KSpace()
{
	if (_IsPaused)
		_IsPaused = false;
	else
		_IsPaused = true;
}

void	Game::KOne()
{
	try {
		DisplayFactory::load(_Display, 1);
		_Display->init(_Area.get_Width(), _Area.get_Height());
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		exit(-1);
	}
}

void	Game::KTwo()
{
	try {
		DisplayFactory::load(_Display, 2);
		_Display->init(_Area.get_Width(), _Area.get_Height());
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		KOne();
	}
}

void	Game::KThree()
{
	try {
		DisplayFactory::load(_Display, 3);
		_Display->init(_Area.get_Width(), _Area.get_Height());
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		KOne();
	}
}

void	Game::update()
{
	Point	pos = _Snake.getPosition();
	Point	pos2 = _Snake2.getPosition();

	if (pos.x < 0 || pos.y < 0 || pos.x >= _Area.get_Width() ||
		pos.y >= _Area.get_Height() || _Snake.eatsItself() || (_Multi && _Snake2.isOnBody(pos)))
		_IsRunning = false;
	if (_Multi && (pos2.x < 0 || pos2.y < 0 || pos2.x >= _Area.get_Width() ||
		pos2.y >= _Area.get_Height() || _Snake2.eatsItself() || _Snake.isOnBody(pos2)))
		_IsRunning = false;
	if (isOnObstacle(pos) || isOnObstacle(pos2))
		_IsRunning = false;
	if (pos == _Fruit.get_Position() || pos2 == _Fruit.get_Position())
	{
		_Ate++;
		if (_Fruit.get_Type() == Pattern::fruit2)
			speedincrease();
		if (_Fruit.get_Type() == Pattern::fruit3)
			speeddecrease();
		if (_Fruit.get_Type() == Pattern::fruit4 && pos == _Fruit.get_Position())
			_Snake.scissors();
		else if (_Fruit.get_Type() == Pattern::fruit4)
			_Snake2.scissors();
		else
		{
			if (pos == _Fruit.get_Position())
				_Snake.grow();
			else
				_Snake2.grow();
		}
		popFruit();
		if (_Level * 6 <= _Ate)
		{
			_Level++;
			for (int i = 0; i < 4; i++)
				_Obstacles.push_back(Pattern(getRand(), Pattern::wall));
		}
	}
	if (!(pos == _Fruit.get_Position()))
		_Snake.move();
	if (!(pos2 == _Fruit.get_Position()) && _Multi)
		_Snake2.move();
	_Pts++;
}

void	Game::speeddecrease()
{
	if (_Speed > 0)
		_Speed -= 1;
	return ;
}

void	Game::speedincrease()
{
	if (_Speed < 10)
		_Speed += 1;
	return ;
}

void	Game::menu()
{
	_Display->drawMenu();
	_Display->display();
 	return ;
}

void	Game::display()
{
	_Display->drawField();

	_Display->drawPattern(
		_Fruit.get_Position().x,
		_Fruit.get_Position().y,
		_Fruit.get_Type()
	);
	
	for (const Pattern& part : _Snake.getBody())
	{
		_Display->drawPattern(
			part.get_Position().x,
			part.get_Position().y,
			part.get_Type()
		);
	}
	if (_Multi)
		for (const Pattern& part : _Snake2.getBody())
		{
			_Display->drawPattern(
				part.get_Position().x,
				part.get_Position().y,
				part.get_Type()
			);
		}
	for (const Pattern& obs : _Obstacles)
	{
		_Display->drawPattern(
			obs.get_Position().x,
			obs.get_Position().y,
			obs.get_Type()
		);
	}
	_Display->drawScoring(_Pts, _Level, _Speed, _Ate);

	_Display->display();
}

int		Game::isOnObstacle(Point pt)
{
	for (const Pattern& obs : _Obstacles)
		if (pt == obs.get_Position())
			return 1;
	return 0;
}

Point	Game::getRand()
{
	int		avail = _Area.get_Area() - _Snake.getSize() - _Obstacles.size() - 1;
	if (_Multi)
		avail -= _Snake2.getSize();
	int		pos = std::rand() % avail;
	int		x = 0, y;

	for (y = 0; pos > 0; y++)
	{
		for (x = 0; x < _Area.get_Width(); x++, pos--)
			if (_Snake.isOnBody(Point(x, y)) || isOnObstacle(Point(x, y)) ||
				(_Multi && _Snake2.isOnBody(Point(x, y)))
			)
				pos++;
			else if (pos == 0)
				break;
	}
	if (y)
		y--;
	if (x == _Area.get_Width())
		x = 0;
	return Point(x, y);
}

void	Game::popFruit()
{
	int		num = std::rand() % 99;

	if (num >= 25)
		_Fruit.set_Type(Pattern::fruit1);
	else if (num < 25 && num >= 15)
		_Fruit.set_Type(Pattern::fruit2);
	else if (num < 15 && num >= 5)
		_Fruit.set_Type(Pattern::fruit3);
	else if (num >= 5)
		_Fruit.set_Type(Pattern::fruit4);
	_Fruit.set_Position(getRand());
}
