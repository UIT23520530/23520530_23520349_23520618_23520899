#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <State.hpp>
#include <Game.hpp>

namespace Engine
{
	class SplashState : public State
	{
	private:
		GameDataRef m_data;
		sf::Clock m_clock;
		sf::Sprite m_background;
	public:
		SplashState(GameDataRef data);

		void Init();
		void ProcessInput();
		void Update(float dt);
		void Draw(float dt);

	};
}