#include "SfDisplay.h"

SfDisplay::SfDisplay()
{
	_Key_map[sf::Keyboard::Right] = IDisplay::RIGHT;
	_Key_map[sf::Keyboard::Left] = IDisplay::LEFT;
	_Key_map[sf::Keyboard::Down] = IDisplay::DOWN;
	_Key_map[sf::Keyboard::Up] = IDisplay::UP;
	_Key_map[sf::Keyboard::Space] = IDisplay::SPACE;
	_Key_map[sf::Keyboard::Escape] = IDisplay::ESC;
	_Key_map[sf::Keyboard::Num1] = IDisplay::ONE;
	_Key_map[sf::Keyboard::Num2] = IDisplay::TWO;
	_Key_map[sf::Keyboard::Num3] = IDisplay::THREE;
	return ;
}

SfDisplay::~SfDisplay()
{
	return ;
}

void	SfDisplay::init(int width, int height)
{
	if (!_Texture.create(width * UNIT_SIZE, height * UNIT_SIZE))
		throw std::runtime_error("Failed to create window.");
	_Window.create(sf::VideoMode(width * UNIT_SIZE, height * UNIT_SIZE), "Nibbler");
}

void	SfDisplay::drawPattern(int posX, int posY, int sizeX, int sizeY, Pattern::Type type)
{
	sf::RectangleShape pattern;

	pattern.setSize(sf::Vector2f(sizeX * UNIT_SIZE, sizeY * UNIT_SIZE));
	pattern.setPosition(posX * UNIT_SIZE, posY * UNIT_SIZE);
	if (type == Pattern::bodyLR || type == Pattern::bodyUD || type == Pattern::bodyLU ||
		type == Pattern::bodyLD || type == Pattern::bodyRD || type == Pattern::bodyRU
	)
		pattern.setFillColor(sf::Color::Green);
	else if (type == Pattern::headL || type == Pattern::headR || type == Pattern::headU || type == Pattern::headD)
		pattern.setFillColor(sf::Color::Yellow);
	else if (type == Pattern::fruit1 || type == Pattern::fruit2 || type == Pattern::fruit3 || type == Pattern::fruit4)
		pattern.setFillColor(sf::Color::Red);
	_Texture.draw(pattern);
}

void	SfDisplay::drawField()
{
	_Texture.clear(sf::Color::Black);
}

void	SfDisplay::drawMenu()
{
	return ;
}

void	SfDisplay::drawScoring(int pts, int level, int speed)
{
	(void)pts;
	(void)level;
	(void)speed;
	return ;
}

void	SfDisplay::display()
{
	sf::Sprite sprite(_Texture.getTexture());

	_Texture.display();
	_Window.clear(sf::Color::Black);
	_Window.draw(sprite);
	_Window.display();
}

void	SfDisplay::close()
{
	_Window.close();
}

IDisplay::Key	SfDisplay::getEvent()
{
	sf::Event		event;
	IDisplay::Key	key = IDisplay::NONE;

	while (key == IDisplay::NONE && _Window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			try {
				key = _Key_map.at(event.key.code);
			}
			catch (std::exception& ex) {}
		}
		else if (event.type == sf::Event::Closed)
			key = IDisplay::ESC;
	}
	return key;
}
