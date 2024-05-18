#include <PauseState.hpp>
#include <GameplayState.hpp>
#include <DEFINITIONS.hpp>

#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Image.hpp>

namespace Engine
{
	PauseState::PauseState(GameDataRef data) : m_data(data) {}

	void PauseState::Init()
	{
		std::cout << "Pause State" << std::endl;

		sf::Image image;
		image.create(752, 100, sf::Color::Black);
		sf::Texture texture;
		texture.loadFromImage(image);
		sf::Sprite m_pauseBackground(texture);

		m_pauseBackground.setColor(sf::Color(0, 0, 0, 127));

		m_data->assets.LoadFont("Pause Title",
			PAUSE_TITLE_FILEPATH);
		m_pauseTitle.setFont(m_data->assets.GetFont("Pause Title"));
		m_pauseTitle.setString("PAUSED");
		m_pauseTitle.setPosition((SCREEN_WIDTH / 2) - (m_pauseTitle.getGlobalBounds().
			width / 2) - 175.0f, 100.0f);
		m_pauseTitle.setFillColor(sf::Color::Black);
		m_pauseTitle.setCharacterSize(40);


		m_data->assets.LoadFont("Continue Button",
			CONTINUE_BUTTON_FONT_FILEPATH);
		m_continueButton.setFont(m_data->assets.GetFont("Continue Button"));
		m_continueButton.setString("CONTINUE");
		m_continueButton.setPosition((SCREEN_WIDTH / 2) - (m_continueButton.getGlobalBounds().
			width / 2) - 260.0f, 175.0f);
		m_continueButton.setCharacterSize(25);


		m_data->assets.LoadFont("New Game Button",
			NEW_GAME_BUTTON_FONT_FILEPATH);
		m_newgameButton.setFont(m_data->assets.GetFont("New Game Button"));
		m_newgameButton.setString("NEW GAME");
		m_newgameButton.setPosition((SCREEN_WIDTH / 2) - (m_newgameButton.getGlobalBounds().
			width / 2), 175.0f);
		m_newgameButton.setCharacterSize(25);


	}

	void PauseState::ProcessInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				m_data->sound.stopAllSounds();
				m_data->window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					m_data->states.RemoveState();
					break;
				default:
					break;
				}
			}
			else if (m_data->input.IsTextClicked(m_continueButton, sf::Mouse::Left, m_data->window))
			{
				m_data->sound.m_clickSound.play();
				m_data->sound.playBackgroundMusic();
				m_data->states.RemoveState();
				break;
			}
			else if (m_data->input.IsTextClicked(m_newgameButton, sf::Mouse::Left, m_data->window))
			{
				m_data->sound.m_clickSound.play();
				m_data->sound.playBackgroundMusic();
				m_data->states.AddState(StateRef(new GameplayState(m_data)), true);
			}

			if (event.type == sf::Event::MouseMoved)
			{
				if (m_newgameButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_newgameButton.setFillColor(sf::Color::Yellow);
				}
				else
				{
					m_newgameButton.setFillColor(sf::Color::White);
				}

				if (m_continueButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_continueButton.setFillColor(sf::Color::Yellow);
				}
				else
				{
					m_continueButton.setFillColor(sf::Color::White);
				}
			}
		}
	}

	void PauseState::Update(float dt)
	{

	}

	void PauseState::Draw(float dt)
	{

		m_data->window.draw(m_pauseTitle);
		m_data->window.draw(m_continueButton);
		m_data->window.draw(m_newgameButton);
		m_data->window.draw(m_pauseBackground);

		m_data->window.display();
	}
}