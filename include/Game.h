#ifndef GAME_H
# define GAME_H

# include <map>
# include "IDisplay.h"
# include "ISound.h"
# include "Pattern.h"
# include "Snake.h"
# include "Area.h"
# include "menu.h"

class Game;
typedef void(Game::*GameKey)();

class Game
{
public:
	Game(int x, int y, bool multiplayer);
	~Game();

	void	launch();

private:
	Game();
	Game(const Game&);
	Game& operator=(const Game &);

	Point									getRand();
	void									popFruit();
	Pattern									_Fruit;
	Snake									_Snake;
	Snake									_Snake2;
	Area									_Area;
	std::vector<Pattern>					_Obstacles;
	std::chrono::steady_clock::time_point	_NextRefresh;

	void				listen();
	void				update();
	void				update(Snake&);
	void				display();
	int					isOnObstacle(Point);
	/* Key handlers */
	void				KLeft();
	void				KRight();
	void				KUp();
	void				KDown();
	void				KW();
	void				KA();
	void				KS();
	void				KD();
	void				KEsc();
	void				KSpace();
	void				KOne();
	void				KTwo();
	void				KThree();

	bool				menu();
	void				reset();

	IDisplay			*_Display;
	ISound				*_Sound;
	std::map<IDisplay::Key, GameKey>	_Key_map;
	bool				_IsRunning;
	bool				_IsPaused;
	bool				_Multi;
	int					_Level;
	bool				_PlayedGameover;

	//options pour le menu

//	bool				_music;
//	int					_graphOption; // Ncurses, OpenGL, SFML

};

#endif
