#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Engine
{
	class InputMan
	{
	public:
		InputMan() {}
		~InputMan() {}

		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, 
			sf::RenderWindow& window);
		bool IsTextClicked(sf::Text object, sf::Mouse::Button button,
			sf::RenderWindow& window);

		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};
}