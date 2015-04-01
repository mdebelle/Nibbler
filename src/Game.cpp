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
	_Level(0)
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
	std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now() + std::chrono::milliseconds(200);
	_Snake.setStart(time);
	_Snake2.setStart(time);
	while (_IsRunning)
	{
		display();
		listen();
		if (!_IsPaused)
		{
			update(_Snake);
			if ((_Level + 1) * 6 <= _Snake.getAte() + _Snake2.getAte())
			{
				_Level++;
				for (int i = 0; i < 4; i++)
					_Obstacles.push_back(Pattern(getRand(), Pattern::wall));
			}
			if (_Multi)
				update(_Snake2);
			if (_Multi && (_Snake2.isOnBody(_Snake.getPosition()) ||
				_Snake.isOnBody(_Snake2.getPosition())))
				_IsRunning = false;
		}
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
	{
		_IsPaused = false;
		std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now() + std::chrono::milliseconds(200);
		_Snake.setStart(time);
		_Snake2.setStart(time);
	}
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

void	Game::update(Snake& snake)
{
	Point	pos = snake.getPosition();

	if (pos.x < 0 || pos.y < 0 || pos.x >= _Area.get_Width() ||
		pos.y >= _Area.get_Height() || snake.eatsItself() || isOnObstacle(pos)
	)
		_IsRunning = false;
	if (pos == _Fruit.get_Position())
	{
		snake.eat(_Fruit.get_Type());
		popFruit();
	}

	snake.move(_Level);
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
	_Display->drawScoring(_Snake.getPts(), _Level, _Snake.getSpeed(), _Snake.getAte());

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

	if (num >= 30)
		_Fruit.set_Type(Pattern::fruit1);
	else if (num < 30 && num >= 20)
		_Fruit.set_Type(Pattern::fruit2);
	else if (num < 20 && num >= 10)
		_Fruit.set_Type(Pattern::fruit3);
	else if (num < 10)
		_Fruit.set_Type(Pattern::fruit4);
	_Fruit.set_Position(getRand());
}
