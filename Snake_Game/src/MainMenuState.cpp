#include <MainMenuState.hpp>
#include <OptionState.hpp>
#include <GameOverState.hpp>
#include <DEFINITIONS.hpp>

#include <iostream>

#include <SFML/Window/Event.hpp>

namespace Engine
{
	MainMenuState::MainMenuState(GameDataRef data) : m_data(data) {}

	void MainMenuState::Init()
	{
		std::cout << "Main Menu State" << std::endl;

		m_data->assets.LoadTexture("Main Menu Background", 
			MAIN_MENU_BACKGROUND_FILEPATH);
		m_data->assets.LoadTexture("Game Title", 
			GAME_TITLE_FILEPATH);
		m_data->assets.LoadTexture("Play Button", 
			PLAY_BUTTON_FILEPATH);

		m_background.setTexture(m_data->assets.GetTexture("Main Menu Background"));
		m_title.setTexture(m_data->assets.GetTexture("Game Title"));
		m_playButton.setTexture(m_data->assets.GetTexture("Play Button"));

		m_playButton.setPosition((SCREEN_WIDTH / 2) - (m_playButton.getGlobalBounds().
			width / 2) - 135.0f, (SCREEN_HEIGHT / 2) - (m_playButton.getGlobalBounds().
			height / 2) + 125.0f);
	}

	void MainMenuState::ProcessInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				m_data->sound.stopAllSounds();
				m_data->window.close();
			}

			if (m_data->input.IsSpriteClicked(m_playButton, sf::Mouse::Left,
				m_data->window))
			{
				m_data->sound.m_clickSound.play();
				m_data->states.AddState(StateRef(new OptionState(m_data)), true);
			}
		}
	}

	void MainMenuState::Update(float dt)
	{
		
	}

	void MainMenuState::Draw(float dt)
	{
		m_data->window.clear();

		m_data->window.draw(m_background);
		m_data->window.draw(m_title);
		m_data->window.draw(m_playButton);

		m_data->window.display();
	}
}