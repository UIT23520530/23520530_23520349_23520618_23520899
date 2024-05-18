#include <SplashState.hpp>
#include <MainMenuState.hpp>
#include <DEFINITIONS.hpp>

#include <iostream>

#include <SFML/Window/Event.hpp>

namespace Engine
{
	SplashState::SplashState(GameDataRef data) : m_data(data) {}

	void SplashState::Init()
	{
		m_data->assets.LoadTexture("Splash State Background",
			SPLASH_SCENE_BACKGROUND_FILEPATH);

		m_background.setTexture(m_data->assets.GetTexture("Splash State Background"));
	}

	void SplashState::ProcessInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				m_data->sound.stopAllSounds();
				m_data->window.close();
			}
		}
	}

	void SplashState::Update(float dt)
	{
		if (m_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			m_data->states.AddState(StateRef(new MainMenuState(m_data)), true);
		}
	}

	void SplashState::Draw(float dt)
	{
		m_data->window.clear();
		m_data->window.draw(m_background);
		m_data->window.display();
	}
}