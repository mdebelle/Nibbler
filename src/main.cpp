#include <iostream>
#include <cstdlib>
#include "Game.h"

static int		nan(const char *nb)
{
	for (int i = 0; nb[i]; i++)
		if (nb[i] < '0' || nb[i] > '9')
			return 1;
	return 0;
}

int		main(int ac, char **av)
{
	if (ac != 3)
		std::cerr << "Usage : Nibbler <size x> <size y>." << std::endl;
	else
	{
		int x = std::atoi(av[1]);
		int y = std::atoi(av[2]);

		if (nan(av[1]) || nan(av[2]))
			std::cerr << "Error : parameter must be a positive number" << std::endl;
		else if (x < 25 || y < 15 || x > 70 || y > 50)
			std::cerr << "Error : size must be between 25x15 and 70x50 inclusive" << std::endl;
		else
		{
			Game game(x, y);
			game.launch();
		}
	}

	return (0);
}
