#ifndef GAME_H
# define GAME_H

# include <map>
# include "IDisplay.h"
# include "Pattern.h"
# include "Snake.h"
# include "Area.h"

class Game;
typedef void(Game::*GameKey)();

class Game
{
public:
	Game(int x, int y);
	~Game();

	void	launch();

private:
	Game();
	Game(const Game&);
	Game operator=(const Game &);

	void				popFruit();
	Pattern				_Fruit;
	Snake				_Snake;
	Snake::Direction	_NextMove;
	Area				_Area;

	void				listen();
	void				update();
	void				display();

	/* Key handlers */
	void				KLeft();
	void				KRight();
	void				KUp();
	void				KDown();
	void				KEsc();
	void				KSpace();
	void				KOne();
	void				KTwo();
	void				KThree();

	IDisplay			*_Display;
	std::map<IDisplay::Key, GameKey>	_Key_map;
	bool				_IsRunning;
};

#endif
