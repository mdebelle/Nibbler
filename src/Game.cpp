#include "Game.h"

Game::Game() : _Fruit(Point(0, 0), Pattern::fruit)
{
	return ;
}

Game::~Game()
{	
	return ;
}

void	Game::listen()
{
	IDisplay::Key key = _Display->getEvent();

	(this->*(_Key_map.at(key)))();
	return ;
}

void	Game::  KLeft()
{
	_Snake.move(Snake::LEFT);
	return ;
}

void	Game::KRight()
{
	_Snake.move(Snake::RIGHT);
	return ;
}

void	Game::KUp()
{
	_Snake.move(Snake::UP);
	return ;
}

void	Game::KDown()
{
	_Snake.move(Snake::DOWN);
	return ;
}

void	Game::KEsc()
{
	_IsRunning = false;
	return ;
}

void	Game::KSpace()
{
	
}

void	Game::KOne()
{

}

void	Game::KTwo()
{

}

void	Game::KThree()
{

}

void	Game::update()
{
	
}

void	Game::display()
{
	_Display->refresh();
}

void	popFruit()
{

}
