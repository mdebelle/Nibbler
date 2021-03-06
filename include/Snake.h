#ifndef SNAKE_H
# define SNAKE_H

# include <map>
# include <vector>
# include <chrono>
# include "Pattern.h"
# include "tools.h"

class Snake;
typedef void(Snake::*DirSnake)();

class Snake
{
	public:
		enum Direction
		{
			UP = -2,
			LEFT = -1,
			RIGHT = 1,
			DOWN = 2
		};

		Snake(int x, int y, int player);
		~Snake();

		void							setAltColor();
		void							move(int level);
		void							setDirection(Direction dir);
		Point							getPosition() const;
		bool							isOnBody(Point) const;
		bool							eatsItself() const;
		const std::vector<Pattern>&		getBody() const;
		int								getSize() const;
		int								getSpeed() const;
		int								getPts() const;
		int								getPlayer() const;
		int								getAte() const;
		void							speedUp();
		void							speedDown();
		void							setPts(int);
		void							eat(Pattern::Type);
		void							setStart(std::chrono::steady_clock::time_point& time);
		void							reset(int x, int y);

	private:
		std::vector<Direction>					_Direction;
		std::vector<Pattern>					_Body;
		std::map<Snake::Direction, DirSnake>	_SnakeDir;
		bool									_AltColor;
		int										_Speed;
		int										_Pts;
		int										_Ate;
		int										_SizeChange;
		std::chrono::steady_clock::time_point	_NextMove;
		int										_Player;

		void									updateTail();
		void									DirLeft();
		void									DirRight();
		void									DirUp();
		void									DirDown();
		void									scissors();
		void									grow();

		Snake();
		Snake(const Snake&);
		Snake&							operator=(const Snake&);
};

#endif
