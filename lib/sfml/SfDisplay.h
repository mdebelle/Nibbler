#ifndef SFDISPLAY_H
# define SFDISPLAY_H

# include <map>
# include <SFML/Graphics.hpp>
# include "IDisplay.h"

# define UNIT_SIZE	25

class SfDisplay : public IDisplay
{
	public:
		SfDisplay();
		~SfDisplay();

		void			init(int width, int height) override;
		void			drawPattern(
			int posX,
			int posY,
			Pattern::Type type
		) override;
		void			drawMenu() override;
		void			drawField() override;
		void			drawScoring(int pts, int level, int speed, int ate) override;
		IDisplay::Key	getEvent() override;
		void			close() override;
		void			display() override;

	private:
		sf::Vector2i		_Size;
		sf::RenderWindow	_Window;
		sf::RenderTexture	_Texture;
		sf::Texture			_Spritesheet;
		sf::Sprite			_Sprite;
		std::map<sf::Keyboard::Key, IDisplay::Key>	_Key_map;
		std::map<Pattern::Type, sf::Vector2i>		_SnakeAssets;
};

#endif
