#ifndef SNAKE_H
# define SNAKE_H

# include <map>
# include <vector>
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

		Snake(int x, int y);
		~Snake();

		void							move();
		void							scissors();
		void							grow();
		void							slim();
		void							setDirection(Direction dir);
		Direction						getDirection() const;
		Point							getPosition() const;
		bool							isOnBody(Point) const;
		bool							eatsItself() const;
		const std::vector<Pattern>&		getBody() const;
		int								getSize() const;
		void							DirLeft();
		void							DirRight();
		void							DirUp();
		void							DirDown();

	private:
		Direction								_Direction;
		Direction								_DirectionFrom;
		std::vector<Pattern>					_Body;
		int										_Alive;
		std::map<Snake::Direction, DirSnake>	_SnakeDir;

		Snake();
		Snake(const Snake&);
		Snake&							operator=(const Snake&);
};

#endif
