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
			UP = -2,
			LEFT = -1,
			RIGHT = 1,
			DOWN = 2
		};

		Snake(int x, int y);
		~Snake();

		void					move();
		void					grow();
		void					slim();
		void					setDirection(Direction dir);
		Point					getPosition() const;
		bool					isOnBody(Point) const;
		bool					eatsItself() const;
		const std::vector<Pattern>& getBody() const;

	private:
		Direction				_Direction;
		std::vector<Pattern>	_Body;
		int						_Alive;

		Snake();
		Snake(const Snake&);
		Snake&					operator=(const Snake&);
};

#endif
