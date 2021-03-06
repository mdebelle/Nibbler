#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "DisplayFactory.h"
#include "SoundFactory.h"

Game::Game(int x, int y) :
	_Fruit(Point(0, 0), Pattern::fruit1),
	_Snake((x / 2) - 2, y / 2, 1),
	_Snake2((x / 2) - 2, y / 2 - 2, 2),
	_Area(Point(x, y)),
	_Display(nullptr),
	_Sound(nullptr),
	_IsRunning(false),
	_IsPaused(false),
	_Multi(false),
	_Level(0),
	_PlayedGameover(false)
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

	DisplayFactory::load(_Display, 1, x, y);
	SoundFactory::load(_Sound, 1);
	std::srand(std::time(nullptr));
	popFruit();
	return ;
}

Game::~Game()
{
	_Display->close();
	if (_Sound)
		_Sound->close();
	return ;
}

void	Game::launch()
{
	while (menu())
	{
		reset();
		if (_Sound)
			_Sound->play(ISound::MUSIC);
		std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now() + std::chrono::milliseconds(200);
		_Snake.setStart(time);
		_Snake2.setStart(time);
		_NextRefresh = std::chrono::steady_clock::now();
		while (_IsRunning || std::chrono::steady_clock::now() < time)
		{
			if (std::chrono::steady_clock::now() >= _NextRefresh)
			{
				display();
				_NextRefresh += std::chrono::milliseconds(50);
				listen();
				if (!_IsPaused && _IsRunning)
				{
					update();
					time = std::chrono::steady_clock::now() + std::chrono::seconds(1);
				}
			}
			if (_Sound && !_IsRunning && !_PlayedGameover)
			{
				_Sound->stop(ISound::MUSIC);
				_Sound->play(ISound::GAMEOVER);
				_PlayedGameover = true;
			}
		}
	}
}

void	Game::update()
{
	update(_Snake);
	if ((_Level + 1) * 6 <= _Snake.getAte() + _Snake2.getAte())
	{
		if (_Sound)
			_Sound->play(ISound::LEVELUP);
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

void	Game::listen()
{
	IDisplay::Key key = _Display->getEvent();

	if (key != IDisplay::NONE && key != IDisplay::M)
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
	_PlayedGameover = true;
	if (_Sound)
		_Sound->stop(ISound::MUSIC);
	return ;
}

void	Game::KSpace()
{
	if (_IsPaused)
	{
		_IsPaused = false;
		if (_Sound)
			_Sound->play(ISound::MUSIC);
		std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now() + std::chrono::milliseconds(200);
		_Snake.setStart(time);
		_Snake2.setStart(time);
	}
	else
	{
		if (_Sound)
			_Sound->pause(ISound::MUSIC);
		_IsPaused = true;
	}
}

void	Game::KOne()
{
	try {
		DisplayFactory::load(_Display, 1, _Area.get_Width(), _Area.get_Height());
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		exit(-1);
	}
}

void	Game::KTwo()
{
	try {
		DisplayFactory::load(_Display, 2, _Area.get_Width(), _Area.get_Height());
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		KOne();
	}
}

void	Game::KThree()
{
	try {
		DisplayFactory::load(_Display, 3, _Area.get_Width(), _Area.get_Height());
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
		pos.y >= _Area.get_Height() || snake.eatsItself() || isOnObstacle(pos))
	{
		_IsRunning = false;
	}
	if (pos == _Fruit.get_Position())
	{
		snake.eat(_Fruit.get_Type());
		if (_Sound)
		{
			switch (_Fruit.get_Type())
			{
				case Pattern::fruit1:
					_Sound->play(ISound::FRUIT1);
					break;
				case Pattern::fruit2:
					_Sound->play(ISound::FRUIT2);
					break;
				case Pattern::fruit3:
					_Sound->play(ISound::FRUIT3);
					break;
				case Pattern::fruit4:
					_Sound->play(ISound::FRUIT4);
					break;
				default:
					break;
			}
		}
		popFruit();
	}

	snake.move(_Level);
}

bool	Game::menu()
{
	IDisplay::Key key = _Display->getEvent();
	
	while (42)
	{	
		key = _Display->getEvent();
		if (key == IDisplay::M)
			_Multi = (_Multi == true) ? false : true;
		else if (key == IDisplay::S)
		{
			if (_Sound)
				SoundFactory::close(_Sound);
			else
			{
				try { SoundFactory::load(_Sound, 1); }
				catch (std::exception& ex) {}
			}
		}
		else if (key == IDisplay::SPACE)
			break ;
		else if (key == IDisplay::ESC)
			return false ;
		else if (key == IDisplay::ONE)
			KOne();
		else if (key == IDisplay::TWO)
			KTwo();
		else if (key == IDisplay::THREE)
			KThree();
		_Display->drawMenu(_Multi, _Sound != nullptr);
		_Display->display();
 	}
 	return true;
}


void	Game::reset()
{
	_IsRunning = true;
	_PlayedGameover = false;
	_Snake.reset((_Area.get_Width() / 2) - 2, _Area.get_Height() / 2);
	_Snake2.reset((_Area.get_Width() / 2) - 2, _Area.get_Height() / 2 - 2);
	_Snake2.setAltColor();
	_Obstacles.clear();
	_Level = 0;
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

	_Display->drawScoring(_Snake.getPts(), 1, _Level, _Multi);
	if (_Multi == true)
		_Display->drawScoring(_Snake2.getPts(), 2, _Level, _Multi);

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
				(_Multi && _Snake2.isOnBody(Point(x, y))))
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
