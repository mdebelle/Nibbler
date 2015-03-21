#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "DisplayFactory.h"

Game::Game(int x, int y) :
	_Fruit(Point(0, 0), Pattern::fruit),
	_Snake((x / 2) - 1, y / 2),
	_Area(Point(x, y)),
	_Display(nullptr),
	_IsRunning(false)
{
	_Key_map[IDisplay::ESC] = &Game::KEsc;
	_Key_map[IDisplay::SPACE] = &Game::KSpace;
	_Key_map[IDisplay::UP] = &Game::KUp;
	_Key_map[IDisplay::RIGHT] = &Game::KRight;
	_Key_map[IDisplay::LEFT] = &Game::KLeft;
	_Key_map[IDisplay::DOWN] = &Game::KDown;
	_Key_map[IDisplay::ONE] = &Game::KOne;
	_Key_map[IDisplay::TWO] = &Game::KTwo;
	_Key_map[IDisplay::THREE] = &Game::KThree;
	DisplayFactory::load(_Display, 1);
	_Display->init(x, y);
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

	while (_IsRunning)
	{
		display();
		usleep(200000);
		listen();
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
	_Snake.setDirection(Snake::LEFT);
	return ;
}

void	Game::KRight()
{
	_Snake.setDirection(Snake::RIGHT);
	return ;
}

void	Game::KUp()
{
	_Snake.setDirection(Snake::UP);
	return ;
}

void	Game::KDown()
{
	_Snake.setDirection(Snake::DOWN);
	return ;
}

void	Game::KEsc()
{
	_IsRunning = false;
	return ;
}

void	Game::KSpace()
{
	IDisplay::Key key = IDisplay::NONE;
	while (key != IDisplay::SPACE)
	{
		key = _Display->getEvent();
		if (key == IDisplay::ESC)
		{
			_IsRunning = false;
			key = IDisplay::SPACE;
		}
		else if (key == IDisplay::ONE || key == IDisplay::TWO || key == IDisplay::THREE)
			(this->*(_Key_map.at(key)))();
	}
}

void	Game::KOne()
{
	DisplayFactory::load(_Display, 1);
	_Display->init(_Area.get_Width(), _Area.get_Height());
}

void	Game::KTwo()
{
	DisplayFactory::load(_Display, 2);
	_Display->init(_Area.get_Width(), _Area.get_Height());
}

void	Game::KThree()
{
	DisplayFactory::load(_Display, 3);
	_Display->init(_Area.get_Width(), _Area.get_Height());
}


void	Game::update()
{
	Point	pos = _Snake.getPosition();
	if (pos.x < 0 || pos.y < 0 || pos.x >= _Area.get_Width() ||
		pos.y >= _Area.get_Height() || _Snake.eatsItself())
		_IsRunning = false;
	if (_Snake.getPosition() == _Fruit.get_Position())
	{
		_Snake.grow();
		popFruit();
	}
	else
		_Snake.move();
}

void	Game::display()
{
	const std::vector<Pattern>& snake = _Snake.getBody();
	_Display->drawField();
	_Display->drawPattern(
		_Fruit.get_Position().x,
		_Fruit.get_Position().y,
		_Fruit.get_Size().x,
		_Fruit.get_Size().y,
		_Fruit.get_Type()
	);
	for (const Pattern& part : snake)
	{
		_Display->drawPattern(
			part.get_Position().x,
			part.get_Position().y,
			part.get_Size().x,
			part.get_Size().y,
			part.get_Type()
		);
	}
	_Display->drawPattern(
		snake[0].get_Position().x,
		snake[0].get_Position().y,
		snake[0].get_Size().x,
		snake[0].get_Size().y,
		Pattern::head
	);
	_Display->display();
}

void	Game::popFruit()
{
	int		fruit = std::rand() % (_Area.get_Area() - _Snake.getSize() - 1);
	int		x = 0, y;

	for (y = 0; fruit > 0; y++)
	{
		for (x = 0; x < _Area.get_Width(); x++, fruit--)
			if (_Snake.isOnBody(Point(x, y)))
				fruit++;
			else if (fruit == 0)
				break;
	}
	if (y)
		y--;
	if (x == 15)
		x = 0;
	_Fruit.set_Position(Point(x, y));
}
