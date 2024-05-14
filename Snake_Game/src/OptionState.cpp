#include <OptionState.hpp>
#include <GameplayState.hpp>
#include <DEFINITIONS.hpp>

#include <iostream>

#include <SFML/Window/Event.hpp>

namespace Engine
{
	OptionState::OptionState(GameDataRef data) : m_data(data) {}

	void OptionState::Init()
	{
		std::cout << "Option State" << std::endl;

		m_data->assets.LoadTexture("Game Background",
			GAME_BACKGROUND_FILEPATH);
		m_data->assets.LoadTexture("Game Title",
			GAME_TITLE_FILEPATH);
		m_data->assets.LoadFont("Gameplay Button Font",
			GAMEPLAY_BUTTON_FONT_FILEPATH);
		m_data->assets.LoadFont("Highscore Button Font",
			HIGHSCORE_BUTTON_FONT_FILEPATH);
		m_data->assets.LoadFont("Exit Button Font",
			EXIT_BUTTON_FONT_FILEPATH);

		m_background.setTexture(m_data->assets.GetTexture("Game Background"));
		m_title.setTexture(m_data->assets.GetTexture("Game Title"));
		m_gameplayButton.setFont(m_data->assets.GetFont("Gameplay Button Font"));
		m_highscoreButton.setFont(m_data->assets.GetFont("Highscore Button Font"));
		m_exitButton.setFont(m_data->assets.GetFont("Exit Button Font"));

		m_gameplayButton.setString("GAMEPLAY");
		m_highscoreButton.setString("HIGHSCORE");
		m_exitButton.setString("EXIT");

		m_exitButton.setPosition(20.0f, SCREEN_HEIGHT - 40.0f);
		m_gameplayButton.setPosition((SCREEN_WIDTH / 2) - 450.0f, (SCREEN_HEIGHT / 2) -
			(m_gameplayButton.getGlobalBounds().height / 2) + 125.0f);
		m_highscoreButton.setPosition((SCREEN_WIDTH / 2) - 50.0f, (SCREEN_HEIGHT / 2) -
			(m_highscoreButton.getGlobalBounds().height / 2) + 125.0f);
		
		m_gameplayButton.setCharacterSize(35);
		m_highscoreButton.setCharacterSize(35);
	}

	void OptionState::ProcessInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				m_data->window.close();
			}

			if (m_data->input.IsTextClicked(m_gameplayButton, sf::Mouse::Left,
				m_data->window))
			{
				m_data->states.AddState(StateRef(new GameplayState(m_data)), true);
			}

			if (m_data->input.IsTextClicked(m_exitButton, sf::Mouse::Left,
				m_data->window))
			{
				std::cout << "EXIT" << std::endl;
				m_data->window.close();
			}

			if (sf::Event::MouseMoved == event.type)
			{
				if (m_gameplayButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_gameplayButton.setFillColor(sf::Color::Yellow);
				}
				else
				{
					m_gameplayButton.setFillColor(sf::Color::White);
				}

				if (m_highscoreButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_highscoreButton.setFillColor(sf::Color::Yellow);
				}
				else
				{
					m_highscoreButton.setFillColor(sf::Color::White);
				}

				if (m_exitButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_exitButton.setFillColor(sf::Color::Yellow);
				}
				else
				{
					m_exitButton.setFillColor(sf::Color::White);
				}
			}
		}
	}

	void OptionState::Update(float dt)
	{

	}

	void OptionState::Draw(float dt)
	{
		m_data->window.clear();

		m_data->window.draw(m_background);
		m_data->window.draw(m_title);
		m_data->window.draw(m_gameplayButton);
		m_data->window.draw(m_highscoreButton);
		m_data->window.draw(m_exitButton);

		m_data->window.display();
	}
}