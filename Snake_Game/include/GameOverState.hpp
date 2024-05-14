#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <State.hpp>
#include <Game.hpp>

namespace Engine
{
	class GameOverState : public State
	{
	private:
		GameDataRef m_data;
		sf::Sprite m_title;
		sf::Sprite m_background;
		sf::Sprite m_gameOver;
		sf::Text m_retryButton;
		sf::Text m_exitButton;

	public:
		GameOverState(GameDataRef data);

		void Init();
		void ProcessInput();
		void Update(float dt);
		void Draw(float dt);

	};
}