#ifndef SFDISPLAY_H
# define SFDISPLAY_H

#include "IDisplay.h"

class SfDisplay : public IDisplay
{
	public:
		SfDisplay();
		~SfDisplay();

		void			init(int width, int height) override;
		void			refresh() override;
		IDisplay::Key	getEvent() override;
		void			close() override;
};

#endif
