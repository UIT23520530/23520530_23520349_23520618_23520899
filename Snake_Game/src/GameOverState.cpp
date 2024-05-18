#include <GameOverState.hpp>
#include <GameplayState.hpp>
#include <DEFINITIONS.hpp>

#include <iostream>
#include <fstream>

#include <SFML/Window/Event.hpp>

namespace Engine
{
	GameOverState::GameOverState(GameDataRef data, int score) : m_data(data), m_score(score) {}

	void GameOverState::LoadHighScores()
	{
		std::ifstream readFile("assets/Highscores.txt");

		m_highscores.clear();
		int score;
		while (readFile >> score)
		{
			m_highscores.push_back(score);
		}
		readFile.close();
	}

	void GameOverState::SaveHighScores()
	{
		std::ofstream writeFile("assets/Highscores.txt");

		for (const int& score : m_highscores)
		{
			writeFile << score << std::endl;
		}
		writeFile.close();
	}

	void GameOverState::Init()
	{
		LoadHighScores();

		m_highscores.push_back(m_score);

		std::sort(m_highscores.rbegin(), m_highscores.rend());

		if (m_highscores.size() > 5)
		{
			m_highscores.resize(5);
		}

		SaveHighScores();

		std::cout << "Game Over State" << std::endl;

		m_data->assets.LoadTexture("Game Background",
			GAME_BACKGROUND_FILEPATH);
		m_data->assets.LoadTexture("Game Title",
			GAME_TITLE_FILEPATH);
		m_data->assets.LoadTexture("Game Over Title",
			GAME_OVER_TITLE_FILEPATH);
		m_data->assets.LoadFont("Retry Button",
			RETRY_BUTTON_FONT_FILEPATH);
		m_data->assets.LoadFont("Exit Button",
			EXIT_BUTTON_FONT_FILEPATH);
		m_data->assets.LoadFont("Score Text",
			SCORE_FONT_FILEPATH);
		m_data->assets.LoadFont("Highscore Text",
			SCORE_FONT_FILEPATH);

		m_background.setTexture(m_data->assets.GetTexture("Game Background"));
		m_title.setTexture(m_data->assets.GetTexture("Game Title"));
		m_gameOver.setTexture(m_data->assets.GetTexture("Game Over Title"));
		m_retryButton.setFont(m_data->assets.GetFont("Retry Button"));
		m_exitButton.setFont(m_data->assets.GetFont("Exit Button"));
		m_scoreText.setFont(m_data->assets.GetFont("Score Text"));
		m_highscoreText.setFont(m_data->assets.GetFont("Highscore Text"));
		_score.setFont(m_data->assets.GetFont("Score Text"));
		_best.setFont(m_data->assets.GetFont("Highscore Text"));

		m_retryButton.setString("RETRY");
		m_exitButton.setString("EXIT");
		m_scoreText.setString("SCORE");
		m_highscoreText.setString("BEST");
		_score.setString(std::to_string(m_score));
		_best.setString(std::to_string(m_highscores.front()));

		m_retryButton.setCharacterSize(35);
		m_exitButton.setCharacterSize(35);
		m_scoreText.setFillColor(sf::Color::Cyan);
		m_highscoreText.setFillColor(sf::Color::Cyan);
		_score.setFillColor(sf::Color::Yellow);
		_best.setFillColor(sf::Color::Red);
		_score.setCharacterSize(80);
		_best.setCharacterSize(80);

		m_gameOver.setPosition((SCREEN_WIDTH / 2) - (m_gameOver.getGlobalBounds().
			width / 2) - 118.0f, (SCREEN_HEIGHT / 2) - (m_gameOver.getGlobalBounds().
				height / 2) + 0.0f);
		m_retryButton.setPosition((SCREEN_WIDTH / 2) - (m_retryButton.getGlobalBounds().
			width / 2) - 270.0f, (SCREEN_HEIGHT / 2) - (m_retryButton.getGlobalBounds().
				height / 2) + 300.0f);
		m_exitButton.setPosition((SCREEN_WIDTH / 2) - (m_exitButton.getGlobalBounds().
			width / 2) + 30.0f, (SCREEN_HEIGHT / 2) - (m_exitButton.getGlobalBounds().
				height / 2) + 300.0f);
		m_scoreText.setPosition((SCREEN_WIDTH / 2) - (m_scoreText.getGlobalBounds().
			width / 2) - 260.0f, (SCREEN_HEIGHT / 2) - (m_scoreText.getGlobalBounds().
				height / 2) + 80.0f);
		m_highscoreText.setPosition((SCREEN_WIDTH / 2) - (m_highscoreText.getGlobalBounds().
			width / 2) + 30.0f, (SCREEN_HEIGHT / 2) - (m_highscoreText.getGlobalBounds().
				height / 2) + 80.0f);
		_score.setPosition((SCREEN_WIDTH / 2) - (_score.getGlobalBounds().
			width / 2) - 260.0f, (SCREEN_HEIGHT / 2) - (_score.getGlobalBounds().
				height / 2) + 180.0f);
		_best.setPosition((SCREEN_WIDTH / 2) - (_best.getGlobalBounds().
			width / 2) + 30.0f, (SCREEN_HEIGHT / 2) - (_best.getGlobalBounds().
				height / 2) + 180.0f);
		
	}

	void GameOverState::ProcessInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				m_data->sound.stopAllSounds();
				m_data->window.close();
			}

			if (m_data->input.IsTextClicked(m_retryButton, sf::Mouse::Left,
				m_data->window))
			{
				m_data->sound.m_clickSound.play();
				m_data->sound.playBackgroundMusic();
				m_data->states.AddState(StateRef(new GameplayState(m_data)), true);
			}

			else if (m_data->input.IsTextClicked(m_exitButton, sf::Mouse::Left,
				m_data->window))
			{
				m_data->sound.m_clickSound.play();
				m_data->window.close();
			}

			if (sf::Event::MouseMoved == event.type)
			{
				if (m_retryButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_retryButton.setFillColor(sf::Color::Yellow);
				}
				else
				{
					m_retryButton.setFillColor(sf::Color::White);
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

	void GameOverState::Update(float dt)
	{

	}

	void GameOverState::Draw(float dt)
	{
		m_data->window.clear();

		m_data->window.draw(m_background);
		m_data->window.draw(m_title);
		m_data->window.draw(m_gameOver);
		m_data->window.draw(m_retryButton);
		m_data->window.draw(m_exitButton);
		m_data->window.draw(m_scoreText);
		m_data->window.draw(m_highscoreText);
		m_data->window.draw(_score);
		m_data->window.draw(_best);

		m_data->window.display();
	}
}