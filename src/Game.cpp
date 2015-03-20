#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "DisplayFactory.h"

Game::Game(int x, int y) :
	_Fruit(Point(0, 0), Pattern::fruit),
	_Snake((x / 2) - 1, y / 2),
	_NextMove(Snake::LAST),
	_Area(Point(x, y)),
	_Display(nullptr),
	_IsRunning(false)
{
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
		usleep(500000);
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

void	Game::  KLeft()
{
	_NextMove = Snake::LEFT;
	return ;
}

void	Game::KRight()
{
	_NextMove = Snake::RIGHT;
	return ;
}

void	Game::KUp()
{
	_NextMove = Snake::UP;
	return ;
}

void	Game::KDown()
{
	_NextMove = Snake::DOWN;
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
	if (pos.x < 0 || pos.y < 0 || pos.x > _Area.get_Width() ||
		pos.y > _Area.get_Height() || _Snake.eatsItself())
		_IsRunning = false;
	if (_Snake.getPosition() == _Fruit.get_Position())
	{
		_Snake.grow();
		popFruit();
	}
	else if (_NextMove != Snake::LAST)
		_Snake.moveTo(_NextMove);
	else
		_Snake.move();
	_NextMove = Snake::LAST;
}

void	Game::display()
{
	const std::vector<Pattern>& snake = _Snake.getBody();
	_Display->drawField();
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
		_Fruit.get_Position().x,
		_Fruit.get_Position().y,
		_Fruit.get_Size().x,
		_Fruit.get_Size().y,
		_Fruit.get_Type()
	);
	_Display->display();
}

void	Game::popFruit()
{
	Point	pos(0, 0);

	do
	{
		pos.y = std::rand() % _Area.get_Height();
		pos.x = std::rand() % _Area.get_Width();

	} while (_Snake.isOnBody(pos));
	_Fruit.set_Position(pos);
}
