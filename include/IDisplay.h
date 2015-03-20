#ifndef IDISPLAY_H
# define IDISPLAY_H

#include "Pattern.h"

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

		virtual ~IDisplay() {};

		virtual void	init(int width, int height) = 0;
		virtual Key		getEvent() = 0;
		virtual void	close() = 0;

		virtual void	drawField() = 0;
		virtual void	drawPattern(
			int posX,
			int posY,
			int sizeX,
			int SizeY,
			Pattern::Type type
		) = 0;
		virtual void	display() = 0;
};

#endif
