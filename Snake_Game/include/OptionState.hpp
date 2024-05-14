#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <State.hpp>
#include <Game.hpp>

namespace Engine
{
	class OptionState : public State
	{
	private:
		GameDataRef m_data;
		sf::Sprite m_background;
		sf::Sprite m_title;
		sf::Text m_gameplayButton;
		sf::Text m_highscoreButton;
		sf::Text m_exitButton;
	public:
		OptionState(GameDataRef data);

		void Init();
		void ProcessInput();
		void Update(float dt);
		void Draw(float dt);

	};
}