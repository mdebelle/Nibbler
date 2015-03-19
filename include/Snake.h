#ifndef SNAKE_H
# define SNAKE_H

# include <vector>
# include "Pattern.h"
# include "tools.h"

class Snake
{
	public:
		enum Direction
		{
			LAST = 0,
			UP = -2,
			LEFT = -1,
			RIGHT = 1,
			DOWN = 2
		};

		Snake(int x, int y);
		~Snake();

		void					move();
		void					moveTo(Direction dir);
		void					grow();
		void					slim();
		Point					getPosition() const;
		bool					isOnBody(Point) const;
		bool					eatsItself() const;

	private:
		Direction				_Direction;
		std::vector<Pattern>	_Body;
		int						_Alive;

		Snake();
		Snake(const Snake&);
		Snake					operator=(const Snake&);
};

#endif
