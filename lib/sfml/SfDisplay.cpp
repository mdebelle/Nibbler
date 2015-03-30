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

	_SnakeAssets[Pattern::bodyUD] = {0, 0};
	_SnakeAssets[Pattern::bodyLR] = {0, 1};
	_SnakeAssets[Pattern::bodyLU] = {0, 2};
	_SnakeAssets[Pattern::bodyRU] = {0, 3};
	_SnakeAssets[Pattern::bodyRD] = {0, 4};
	_SnakeAssets[Pattern::bodyLD] = {0, 5};
	_SnakeAssets[Pattern::headD] = {0, 6};
	_SnakeAssets[Pattern::headU] = {0, 7};
	_SnakeAssets[Pattern::headL] = {0, 8};
	_SnakeAssets[Pattern::headR] = {0, 9};
	_SnakeAssets[Pattern::tailD] = {1, 0};
	_SnakeAssets[Pattern::tailU] = {1, 1};
	_SnakeAssets[Pattern::tailL] = {1, 2};
	_SnakeAssets[Pattern::tailR] = {1, 3};
	_SnakeAssets[Pattern::fruit1] = {1, 5};
	_SnakeAssets[Pattern::fruit2] = {1, 4};
	_SnakeAssets[Pattern::fruit3] = {1, 6};
	_SnakeAssets[Pattern::fruit4] = {1, 7};
	_SnakeAssets[Pattern::wall] = {1, 8};

	return ;
}

SfDisplay::~SfDisplay()
{
	return ;
}

void	SfDisplay::init(int width, int height)
{
	if (!_SnakeSpritesheet.loadFromFile("lib/sfml/snake.png"))
		throw std::runtime_error("Failed to load snake spritesheet (snake.png).");
	_SnakeSprite.setTexture(_SnakeSpritesheet);
	if (!_Texture.create(width * UNIT_SIZE, height * UNIT_SIZE))
		throw std::runtime_error("Failed to create window.");
	_Window.create(sf::VideoMode(width * UNIT_SIZE, height * UNIT_SIZE), "Nibbler");
}

void	SfDisplay::drawPattern(int posX, int posY, int sizeX, int sizeY, Pattern::Type type)
{
	_SnakeSprite.setPosition(posX * UNIT_SIZE, posY * UNIT_SIZE);
	_SnakeSprite.setTextureRect( {
		_SnakeAssets[type].x * UNIT_SIZE,
		_SnakeAssets[type].y * UNIT_SIZE,
		sizeX * UNIT_SIZE, sizeY * UNIT_SIZE
	} );
	_Texture.draw(_SnakeSprite);
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
