#include "SfDisplay.h"

SfDisplay::SfDisplay()
{
	_Key_map[sf::Keyboard::Right] = IDisplay::RIGHT;
	_Key_map[sf::Keyboard::Left] = IDisplay::LEFT;
	_Key_map[sf::Keyboard::Down] = IDisplay::DOWN;
	_Key_map[sf::Keyboard::Up] = IDisplay::UP;
	_Key_map[sf::Keyboard::W] = IDisplay::W;
	_Key_map[sf::Keyboard::A] = IDisplay::A;
	_Key_map[sf::Keyboard::S] = IDisplay::S;
	_Key_map[sf::Keyboard::D] = IDisplay::D;
	_Key_map[sf::Keyboard::M] = IDisplay::M;
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
	_SnakeAssets[Pattern::bodyUD2] = {3, 0};
	_SnakeAssets[Pattern::bodyLR2] = {3, 1};
	_SnakeAssets[Pattern::bodyLU2] = {3, 2};
	_SnakeAssets[Pattern::bodyRU2] = {3, 3};
	_SnakeAssets[Pattern::bodyRD2] = {3, 4};
	_SnakeAssets[Pattern::bodyLD2] = {3, 5};
	_SnakeAssets[Pattern::headD2] = {3, 6};
	_SnakeAssets[Pattern::headU2] = {3, 7};
	_SnakeAssets[Pattern::headL2] = {3, 8};
	_SnakeAssets[Pattern::headR2] = {3, 9};
	_SnakeAssets[Pattern::tailD2] = {4, 0};
	_SnakeAssets[Pattern::tailU2] = {4, 1};
	_SnakeAssets[Pattern::tailL2] = {4, 2};
	_SnakeAssets[Pattern::tailR2] = {4, 3};

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
	if (!_Font.loadFromFile("lib/sfml/font.ttf"))
		throw std::runtime_error("Failed to load font (font.ttf).");
	_Sprite.setTexture(_Spritesheet);
	if (!_Texture.create((width + 2) * UNIT_SIZE, (height + 4) * UNIT_SIZE))
		throw std::runtime_error("Failed to create window.");
	_Window.create(sf::VideoMode((width + 2) * UNIT_SIZE, (height + 4) * UNIT_SIZE), "Nibbler");
}

void	SfDisplay::drawPattern(int posX, int posY, Pattern::Type type)
{
	_Sprite.setPosition((posX + 1) * UNIT_SIZE, (posY + 1) * UNIT_SIZE);
	_Sprite.setTextureRect( {
		_SnakeAssets[type].x * UNIT_SIZE,
		_SnakeAssets[type].y * UNIT_SIZE,
		UNIT_SIZE, UNIT_SIZE
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
	for (int i = 1; i <= _Size.x; i++)
	{
		_Sprite.setPosition(i * UNIT_SIZE, 0);
		_Texture.draw(_Sprite);
	}
	_Sprite.setPosition((_Size.x + 1) * UNIT_SIZE, 0);
	_Sprite.setTextureRect({2 * UNIT_SIZE, 5 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
	_Texture.draw(_Sprite);
	for (int j = 1; j <= _Size.y; j++)
	{
		_Sprite.setPosition(0, j * UNIT_SIZE);
		_Sprite.setTextureRect({2 * UNIT_SIZE, 3 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
		_Texture.draw(_Sprite);
		_Sprite.setTextureRect({2 * UNIT_SIZE, 0 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
		for (int i = 1; i <= _Size.x; i++)
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
	for (int i = 1; i <= _Size.x; i++)
	{
		_Sprite.setPosition(i * UNIT_SIZE, (_Size.y + 1) * UNIT_SIZE);
		_Texture.draw(_Sprite);
	}
	_Sprite.setPosition((_Size.x + 1) * UNIT_SIZE, (_Size.y + 1) * UNIT_SIZE);
	_Sprite.setTextureRect({2 * UNIT_SIZE, 6 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
	_Texture.draw(_Sprite);

	_Sprite.setTextureRect({2 * UNIT_SIZE, 9 * UNIT_SIZE, UNIT_SIZE, UNIT_SIZE});
	for (int j = _Size.y + 2; j <= _Size.y + 3; j++)
		for (int i = 0; i <= _Size.x + 1; i++)
		{
			_Sprite.setPosition(i * UNIT_SIZE, j * UNIT_SIZE);
			_Texture.draw(_Sprite);
		}
}

void	SfDisplay::drawMenu(bool multi, bool sound)
{
	drawField();

	sf::Text	text("NIBBLER", _Font, UNIT_SIZE * 3);
	text.setColor(sf::Color::Black);
	text.setStyle(sf::Text::Underlined|sf::Text::Bold);
	text.setPosition(UNIT_SIZE * 1.5, UNIT_SIZE);
	_Texture.draw(text);

	sf::String str("Multiplayer: ");
	str += multi ? "enabled" : "disabled";
	str += ". Press 'M' to switch it!";
	text.setStyle(sf::Text::Bold);
	text.setPosition(UNIT_SIZE * 2, UNIT_SIZE * 6);
	text.setCharacterSize(UNIT_SIZE * 0.80);
	text.setString(str);
	_Texture.draw(text);

	str = "Sound: ";
	str += sound ? "enabled" : "disabled";
	str += ". Press 'S' to switch it!";
	text.setPosition(UNIT_SIZE * 2, UNIT_SIZE * 7);
	text.setString(str);
	_Texture.draw(text);

	text.setPosition(UNIT_SIZE * 2, UNIT_SIZE * 9);
	text.setString("Press space to start.");
	_Texture.draw(text);
	text.setPosition(UNIT_SIZE * 2, UNIT_SIZE * 10);
	text.setString("Press escape to quit.");
	_Texture.draw(text);
}

void SfDisplay::drawScoring(int pts, int player, int level, bool multi)
{
	sf::Text	text("s", _Font, UNIT_SIZE * 0.80);
	text.setColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	
	if (multi == true)
	{
		if (player == 1)
		{
			text.setString(std::string("Player 1: ") + std::to_string(pts));
			text.setPosition(UNIT_SIZE / 2, (_Size.y + 1) * UNIT_SIZE + UNIT_SIZE / 1.5);
			_Texture.draw(text);
			text.setString(std::string("Level: ") + std::to_string(level));
			text.setPosition((_Size.x / 2) * UNIT_SIZE, (_Size.y + 1) * UNIT_SIZE + UNIT_SIZE / 1.5);
			_Texture.draw(text);
		}
		else if (player == 2)
		{
			text.setString(std::string("Player 2: ") + std::to_string(pts));
			text.setPosition(UNIT_SIZE / 2, (_Size.y + 2) * UNIT_SIZE + UNIT_SIZE / 1.5);
			_Texture.draw(text);
		}
	}
	else
	{
		text.setString(std::string("Score: ") + std::to_string(pts));
		text.setPosition(UNIT_SIZE / 2, (_Size.y + 1) * UNIT_SIZE + UNIT_SIZE / 1.5);
		_Texture.draw(text);
		text.setString(std::string("Level: ") + std::to_string(level));
		text.setPosition(UNIT_SIZE / 2, (_Size.y + 2) * UNIT_SIZE + UNIT_SIZE / 1.5);
		_Texture.draw(text);
	}
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
