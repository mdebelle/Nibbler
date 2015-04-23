#ifndef SFDISPLAY_H
# define SFDISPLAY_H

# include <map>
# include <ncurses.h>
# include "IDisplay.h"
# include "tools.h"

class NcDisplay : public IDisplay
{
	public:
		NcDisplay();
		~NcDisplay();

		void			init(int width, int height) override;
		void			drawField() override;
		void			drawMenu(bool multi) override;
		void			drawScoring(int pts, int player, int level, bool multi) override;
		void			drawPattern(
			int posX,
			int posY,
			Pattern::Type type
		) override;
		void			display() override;
		IDisplay::Key	getEvent() override;
		void			close() override;

	private:
		int				_SizeX;
		int				_SizeY;
		std::map<int, IDisplay::Key>	_Key_map;
		std::map<Pattern::Type, chtype>	_Charset;
};

#endif
