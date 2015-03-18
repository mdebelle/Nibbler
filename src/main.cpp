#include "Game.h"

void initGame(){}

int		main(void)
{

	Game game;

	while(42)
	{

		game.listen();
		game.update();
		game.display();

	}

	return (0);

}
