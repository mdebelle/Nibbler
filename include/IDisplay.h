#ifndef IDISPLAY_H
# define IDISPLAY_H

class IDisplay
{
	public:
		enum Key
		{
			UP,
			LEFT,
			RIGHT,
			DOWN,
			ESC,	// Quit
			SPACE,	// Pause
			ONE,	// NCurses
			TWO,	// OpenGL
			THREE	// SFML
		};

		virtual void	init(int width, int height) = 0;
		virtual void	refresh();
		virtual Key		getEvent();
};

#endif
