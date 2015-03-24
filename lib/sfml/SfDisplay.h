#ifndef SFDISPLAY_H
# define SFDISPLAY_H

# include <map>
# include <SFML/Graphics.hpp>
# include "IDisplay.h"

# define UNIT_SIZE	20

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

	private:
		sf::RenderWindow	_Window;
		sf::RenderTexture	_Texture;
		std::map<sf::Keyboard::Key, IDisplay::Key>	_Key_map;
};

#endif
