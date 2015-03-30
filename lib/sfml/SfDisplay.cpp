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
	_Size.x = width;
	_Size.y = height;
	if (!_Spritesheet.loadFromFile("lib/sfml/snake.png"))
		throw std::runtime_error("Failed to load snake spritesheet (snake.png).");
	_Sprite.setTexture(_Spritesheet);
	if (!_Texture.create((width + 2) * UNIT_SIZE, (height + 2) * UNIT_SIZE))
		throw std::runtime_error("Failed to create window.");
	_Window.create(sf::VideoMode((width + 2) * UNIT_SIZE, (height + 2) * UNIT_SIZE), "Nibbler");
}

void	SfDisplay::drawPattern(int posX, int posY, int sizeX, int sizeY, Pattern::Type type)
{
	_Sprite.setPosition((posX + 1) * UNIT_SIZE, (posY + 1) * UNIT_SIZE);
	_Sprite.setTextureRect( {
		_SnakeAssets[type].x * UNIT_SIZE,
		_SnakeAssets[type].y * UNIT_SIZE,
		sizeX * UNIT_SIZE, sizeY * UNIT_SIZE
	} );
	_Texture.draw(_Sprite);
}

void	SfDisplay::drawField()
{
	_Texture.clear(sf::Color::Black);

	_Sprite.setPosition(0, 0);
	_Sprite.setTextureRect({2 * UNIT_SIZE, 8 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
	_Texture.draw(_Sprite);
	_Sprite.setTextureRect({2 * UNIT_SIZE, 4 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
	for (int i = 1; i < _Size.x + 1; i++)
	{
		_Sprite.setPosition(i * UNIT_SIZE, 0);
		_Texture.draw(_Sprite);
	}
	_Sprite.setPosition((_Size.x + 1) * UNIT_SIZE, 0);
	_Sprite.setTextureRect({2 * UNIT_SIZE, 5 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
	_Texture.draw(_Sprite);
	for (int j = 1; j < _Size.y + 1; j++)
	{
		_Sprite.setPosition(0, j * UNIT_SIZE);
		_Sprite.setTextureRect({2 * UNIT_SIZE, 3 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
		_Texture.draw(_Sprite);
		_Sprite.setTextureRect({2 * UNIT_SIZE, 0 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
		for (int i = 1; i < _Size.x + 1; i++)
		{
			_Sprite.setPosition(i * UNIT_SIZE, j * UNIT_SIZE);
			_Texture.draw(_Sprite);
		}
		_Sprite.setPosition((_Size.x + 1) * UNIT_SIZE, j * UNIT_SIZE);
		_Sprite.setTextureRect({2 * UNIT_SIZE, 1 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
		_Texture.draw(_Sprite);
	}
	_Sprite.setPosition(0, (_Size.y + 1) * UNIT_SIZE);
	_Sprite.setTextureRect({2 * UNIT_SIZE, 7 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
	_Texture.draw(_Sprite);
	_Sprite.setTextureRect({2 * UNIT_SIZE, 2 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
	for (int i = 1; i < _Size.x + 1; i++)
	{
		_Sprite.setPosition(i * UNIT_SIZE, (_Size.y + 1) * UNIT_SIZE);
		_Texture.draw(_Sprite);
	}
	_Sprite.setPosition((_Size.x + 1) * UNIT_SIZE, (_Size.y + 1) * UNIT_SIZE);
	_Sprite.setTextureRect({2 * UNIT_SIZE, 6 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
	_Texture.draw(_Sprite);
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
