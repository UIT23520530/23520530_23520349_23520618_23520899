#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <State.hpp>
#include <Game.hpp>

namespace Engine
{
	class PauseState : public State
	{
	private:
		GameDataRef m_data;
		sf::Text m_pauseTitle;
		sf::Sprite m_pauseBackground;
		sf::Text m_continueButton;
		sf::Text m_newgameButton;
	public:
		PauseState(GameDataRef data);

		void Init();
		void ProcessInput();
		void Update(float dt);
		void Draw(float dt);

	};
}