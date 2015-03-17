int		main(void)
{


	initGame();
	Pattern		Fruit(Point(0,0), Point(1,1), fruit);

	while(42)
	{

		if (t % x == 0 && fruit.get_visible == false)
			popfruit();

		lisenEvent(&Game);
		updateGame();
		displayGame();

	}


	return (0);

}