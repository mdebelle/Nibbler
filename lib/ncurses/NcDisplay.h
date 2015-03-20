#ifndef SFDISPLAY_H
# define SFDISPLAY_H

#include "IDisplay.h"

class NcDisplay : public IDisplay
{
	public:
		NcDisplay();
		~NcDisplay();

		void			init(int width, int height) override;
		void			refresh() override;
		IDisplay::Key	getEvent() override;
		void			close() override;
};

#endif
