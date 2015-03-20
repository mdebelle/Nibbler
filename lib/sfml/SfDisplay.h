#ifndef SFDISPLAY_H
# define SFDISPLAY_H

#include "IDisplay.h"

class SfDisplay : public IDisplay
{
	public:
		SfDisplay();
		~SfDisplay();

		void			init(int width, int height) override;
		void			drawPattern(
			int posX,
			int posY,
			int sizeX,
			int SizeY,
			Pattern::Type type
		) override;
		void			drawField() override;
		IDisplay::Key	getEvent() override;
		void			close() override;
		void			display() override;
};

#endif
