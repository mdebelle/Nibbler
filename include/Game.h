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
	Game& operator=(const Game &);

	Point				getRand();
	int					getPts() const;
	void				popFruit();
	Pattern				_Fruit;
	Snake				_Snake;
	Area				_Area;
	std::vector<Pattern> _Obstacles;

	void				listen();
	void				update();
	void				display();
	int					isOnObstacle(Point);
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
	bool				_IsPaused;
	int					_Level;
	int					_Pts;
};

#endif
