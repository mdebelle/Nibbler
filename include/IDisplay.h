#ifndef IDISPLAY_H
# define IDISPLAY_H

class IDisplay
{
	public:
		enum Key
		{
			NONE,	// Generic one without any effect
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
		virtual void	refresh() = 0;
		virtual Key		getEvent() = 0;
		virtual void	close() = 0;
};

#endif
