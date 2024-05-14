#include <Game.hpp>
#include <SplashState.hpp>

namespace Engine
{
	Game::Game(int width, int height, std::string title)
	{
		m_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close
			| sf::Style::Titlebar);
		m_data->states.AddState(StateRef(new SplashState(m_data)));
		Run();
	}

	void Game::Run()
	{
		float newTime, frameTime, interpolation;
		float currentTime = m_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (m_data->window.isOpen())
		{
			m_data->states.ProcessStateChanges();

			newTime = m_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= deltaTime)
			{
				m_data->states.GetCurrentState()->ProcessInput();
				m_data->states.GetCurrentState()->Update(deltaTime);

				accumulator -= deltaTime;
			}

			interpolation = accumulator / deltaTime;
			m_data->states.GetCurrentState()->Draw(interpolation);
		}
	}
}