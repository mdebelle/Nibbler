#ifndef SFDISPLAY_H
# define SFDISPLAY_H

#include "IDisplay.h"

class GlDisplay : public IDisplay
{
	public:
		GlDisplay();
		~GlDisplay();

		void			init(int width, int height) override;
		void			refresh() override;
		IDisplay::Key	getEvent() override;
		void			close() override;
};

#endif
