#ifndef SFDISPLAY_H
# define SFDISPLAY_H

#include "IDisplay.h"

class GlDisplay : public IDisplay
{
	public:
		GlDisplay();
		~GlDisplay();

		void			init(int width, int height) override;
		void			drawField() override;
		void	drawPattern(
			int posX,
			int posY,
			int sizeX,
			int SizeY,
			Pattern::Type type
		) override;
		void			display() override;
		IDisplay::Key	getEvent() override;
		void			close() override;
};

#endif