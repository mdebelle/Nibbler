#ifndef SNAKE_H
# define SNAKE_H

# include <vector>
# include "Pattern.h"

class Snake
{
	private:
		enum Direction
		{
			UP = -2,
			LEFT = -1,
			RIGHT = 1,
			DOWN = 2
		};

		Direction				_Direction;
		std::vector<Pattern>	_Body;
		int						_Alive;

		Snake();
		Snake(const Snake&);
		Snake					operator=(const Snake&);


	public:
		Snake(int x, int y);
		~Snake();

		void					move();
		void					moveTo(Direction dir);
		void					grow();
		void					slim();
};

#endif
