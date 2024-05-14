#include <GameplayState.hpp>
#include <PauseState.hpp>
#include <GameOverState.hpp>
#include <OptionState.hpp>
#include <DEFINITIONS.hpp>	

#include <iostream>
#include <cmath>	
#include <stdlib.h>
#include <time.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System.hpp>

namespace Engine
{
	GameplayState::GameplayState(GameDataRef data) : m_data(data), m_isclassicButtonClicked(false),
		m_ismodernButtonClicked(false), m_isLevel1Clicked(false), m_isLevel2Clicked(false),
		m_isLevel3Clicked(false), m_isLevel4Clicked(false), m_isLevel5Clicked(false),
		m_direction({ 16.f, 0.f }), m_elapsedTime(0), m_snakeSpeed(1.0), m_isplayButtonClicked(false),
		level(0), m_score(0), m_isPaused(false)
	{
		srand(time(nullptr));
	}

	void GameplayState::Init()
	{
		std::cout << "Gameplay State" << std::endl;

		m_data->assets.LoadTexture("Game Background",
			GAME_BACKGROUND_FILEPATH);
		m_data->assets.LoadTexture("Game Title",
			GAME_TITLE_FILEPATH);
		m_data->assets.LoadFont("Classic Button Font",
			CLASSIC_BUTTON_FONT_FILEPATH);
		m_data->assets.LoadFont("Modern Button Font",
			MODERN_BUTTON_FONT_FILEPATH);
		m_data->assets.LoadFont("Back Button Font",
			BACK_BUTTON_FONT_FILEPATH);
		m_data->assets.LoadFont("Level Button Font",
			LEVEL_BUTTON_FONT_FILEPATH);
		m_data->assets.LoadTexture("Play Button",
			PLAY_BUTTON_2_FILEPATH);
		m_data->assets.LoadTexture("Food", FOOD_FILEPATH);
		m_data->assets.LoadTexture("Snake", SNAKE_FILEPATH);
		m_data->assets.LoadTexture("Wall", WALL_FILEPATH, true);
		m_data->assets.LoadTexture("Grass", GRASS_FILEPATH, true);


		m_data->assets.LoadTexture("Level 1", LEVEL1_BUTTON_FILEPATH);
		m_data->assets.LoadTexture("Level 2", LEVEL2_BUTTON_FILEPATH);
		m_data->assets.LoadTexture("Level 3", LEVEL3_BUTTON_FILEPATH);
		m_data->assets.LoadTexture("Level 4", LEVEL4_BUTTON_FILEPATH);
		m_data->assets.LoadTexture("Level 5", LEVEL5_BUTTON_FILEPATH);


		m_background.setTexture(m_data->assets.GetTexture("Game Background"));
		m_title.setTexture(m_data->assets.GetTexture("Game Title"));
		m_playButton.setTexture(m_data->assets.GetTexture("Play Button"));
		m_classicButton.setFont(m_data->assets.GetFont("Classic Button Font"));
		m_modernButton.setFont(m_data->assets.GetFont("Modern Button Font"));
		m_backButton.setFont(m_data->assets.GetFont("Back Button Font"));
		m_levelButton.setFont(m_data->assets.GetFont("Level Button Font"));

		m_level1.setTexture(m_data->assets.GetTexture("Level 1"));
		m_level2.setTexture(m_data->assets.GetTexture("Level 2"));
		m_level3.setTexture(m_data->assets.GetTexture("Level 3"));
		m_level4.setTexture(m_data->assets.GetTexture("Level 4"));
		m_level5.setTexture(m_data->assets.GetTexture("Level 5"));

		m_classicButton.setString("CLASSIC");
		m_modernButton.setString("MODERN");
		m_backButton.setString("BACK");
		m_levelButton.setString("LEVEL");

		m_backButton.setPosition(20.0f, SCREEN_HEIGHT - 40.0f);
		m_classicButton.setPosition((SCREEN_WIDTH / 2) - 450.0f, (SCREEN_HEIGHT / 2) -
			(m_classicButton.getGlobalBounds().height / 2) + 80.0f);
		m_modernButton.setPosition((SCREEN_WIDTH / 2) - 50.0f, (SCREEN_HEIGHT / 2) -
			(m_modernButton.getGlobalBounds().height / 2) + 80.0f);
		m_levelButton.setPosition((SCREEN_WIDTH / 2) - 450.0f, (SCREEN_HEIGHT / 2) -
			(m_levelButton.getGlobalBounds().height / 2) + 220.0f);
		m_playButton.setPosition((SCREEN_WIDTH / 2) + 174.0f, (SCREEN_HEIGHT / 2) -
			(m_playButton.getGlobalBounds().height / 2) + 160.0f);

		m_level1.setPosition((SCREEN_WIDTH / 2) - 230.0f, (SCREEN_HEIGHT / 2) -
			(m_level1.getGlobalBounds().height / 2) + 220.0f);
		m_level2.setPosition((SCREEN_WIDTH / 2) - 150.0f, (SCREEN_HEIGHT / 2) -
			(m_level2.getGlobalBounds().height / 2) + 220.0f);
		m_level3.setPosition((SCREEN_WIDTH / 2) - 70.0f, (SCREEN_HEIGHT / 2) -
			(m_level3.getGlobalBounds().height / 2) + 220.0f);
		m_level4.setPosition((SCREEN_WIDTH / 2) + 10.0f, (SCREEN_HEIGHT / 2) -
			(m_level4.getGlobalBounds().height / 2) + 220.0f);
		m_level5.setPosition((SCREEN_WIDTH / 2) + 90.0f, (SCREEN_HEIGHT / 2) -
			(m_level5.getGlobalBounds().height / 2) + 220.0f);

		m_classicButton.setCharacterSize(35);
		m_modernButton.setCharacterSize(35);
		m_levelButton.setCharacterSize(35);

		m_levelButton.setFillColor(sf::Color::Cyan);

		m_grass.setTexture(m_data->assets.GetTexture("Grass"));
		m_grass.setTextureRect(sf::IntRect({ 0, 0, GAME_FRAME_WIDTH, GAME_FRAME_HEIGHT }));

		for (auto& wall : m_walls)
		{
			wall.setTexture(m_data->assets.GetTexture("Wall"));
		}

		m_walls[0].setTextureRect({ 0, 0, GAME_FRAME_WIDTH, 16 });
		m_walls[1].setTextureRect({ 0, 0, GAME_FRAME_WIDTH, 16 });
		m_walls[1].setPosition(0, GAME_FRAME_HEIGHT - 16);

		m_walls[2].setTextureRect({ 0, 0, 16, GAME_FRAME_HEIGHT });
		m_walls[3].setTextureRect({ 0, 0, 16, GAME_FRAME_HEIGHT });
		m_walls[3].setPosition(GAME_FRAME_WIDTH - 16, 0);

		m_food.setTexture(m_data->assets.GetTexture("Food"));
		m_food.setPosition(GAME_FRAME_WIDTH / 2, GAME_FRAME_HEIGHT / 2);

		m_snake.Init(m_data->assets.GetTexture("Snake"));

		m_data->assets.LoadFont("Score Font", SCORE_FONT_FILEPATH);
		m_scoreText.setFont(m_data->assets.GetFont("Score Font"));
		m_scoreText.setString("SCORE: " + std::to_string(m_score));
		m_scoreText.setPosition({ 780.0f, 30.0f });
		m_scoreText.setFillColor(sf::Color::Cyan);

		m_data->assets.LoadFont("Level Text", LEVEL_FONT_FILEPATH);
		m_level.setFont(m_data->assets.GetFont("Level Text"));
		
		m_level.setFillColor(sf::Color::Black);
		m_level.setPosition(20.0f, GAME_FRAME_HEIGHT + 20.f);

		m_data->assets.LoadFont("Gamemode Text", GAMEMODE_FONT_FILEPATH);
		m_gamemode.setFont(m_data->assets.GetFont("Gamemode Text"));
		
		m_gamemode.setFillColor(sf::Color::Black);
		m_gamemode.setPosition(GAME_FRAME_WIDTH - 420.0f, GAME_FRAME_HEIGHT + 20.f);
	}

	void GameplayState::ProcessInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				m_data->window.close();
			}

			if (m_data->input.IsSpriteClicked(m_playButton, sf::Mouse::Left, m_data->window))
			{
				if ((m_isclassicButtonClicked && (m_isLevel1Clicked || m_isLevel2Clicked
					|| m_isLevel3Clicked || m_isLevel4Clicked || m_isLevel5Clicked))
					|| (m_ismodernButtonClicked && (m_isLevel1Clicked || m_isLevel2Clicked
						|| m_isLevel3Clicked || m_isLevel4Clicked || m_isLevel5Clicked)))
				{
					m_isplayButtonClicked = true;
				}
			}

			if (m_data->input.IsTextClicked(m_backButton, sf::Mouse::Left,
				m_data->window))
			{
				if ((m_isclassicButtonClicked && (m_isLevel1Clicked || m_isLevel2Clicked
					|| m_isLevel3Clicked || m_isLevel4Clicked || m_isLevel5Clicked))
					|| (m_ismodernButtonClicked && (m_isLevel1Clicked || m_isLevel2Clicked
						|| m_isLevel3Clicked || m_isLevel4Clicked || m_isLevel5Clicked)))
				{
					m_data->states.AddState(StateRef(new GameplayState(m_data)), true);
				}
				else
				{
					m_data->states.AddState(StateRef(new OptionState(m_data)), true);
				}
			}

			if (m_data->input.IsTextClicked(m_classicButton, sf::Mouse::Left,
				m_data->window))
			{
				m_isclassicButtonClicked = true;
				m_ismodernButtonClicked = false;
			}

			else if (m_data->input.IsTextClicked(m_modernButton, sf::Mouse::Left,
				m_data->window))
			{
				m_ismodernButtonClicked = true;
				m_isclassicButtonClicked = false;
			}

			if (sf::Event::MouseMoved == event.type)
			{
				if (m_classicButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_classicButton.setFillColor(sf::Color::Yellow);
				}
				else
				{
					m_classicButton.setFillColor(sf::Color::White);
				}

				if (m_modernButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_modernButton.setFillColor(sf::Color::Yellow);
				}
				else
				{
					m_modernButton.setFillColor(sf::Color::White);
				}

				if (m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_backButton.setFillColor(sf::Color::Yellow);
				}
				else
				{
					m_backButton.setFillColor(sf::Color::White);
				}

				if (m_level1.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_level1.setColor(sf::Color::Yellow);
				}
				else
				{
					m_level1.setColor(sf::Color::White);
				}


				if (m_level2.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_level2.setColor(sf::Color::Yellow);
				}
				else
				{
					m_level2.setColor(sf::Color::White);
				}

				if (m_level3.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_level3.setColor(sf::Color::Yellow);
				}
				else
				{
					m_level3.setColor(sf::Color::White);
				}

				if (m_level4.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_level4.setColor(sf::Color::Yellow);
				}
				else
				{
					m_level4.setColor(sf::Color::White);
				}


				if (m_level5.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_level5.setColor(sf::Color::Yellow);
				}
				else
				{
					m_level5.setColor(sf::Color::White);
				}

				if (m_playButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
				{
					m_playButton.setColor(sf::Color::Green);
				}
				else
				{
					m_playButton.setColor(sf::Color::White);
				}

			}

			if (event.type == sf::Event::KeyPressed)
			{
				sf::Vector2f newDirection = m_direction;
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
				case sf::Keyboard::W:
					newDirection = { 0.f, -16.f };
					break;
				case sf::Keyboard::Down:
				case sf::Keyboard::S:
					newDirection = { 0.f, 16.f };
					break;
				case sf::Keyboard::Right:
				case sf::Keyboard::D:
					newDirection = { 16.f, 0.f };
					break;
				case sf::Keyboard::Left:
				case sf::Keyboard::A:
					newDirection = { -16.f, 0.f };
					break;
				case sf::Keyboard::Escape:
					m_data->states.AddState(StateRef(new PauseState(m_data)), false);
					break;
				default:
					break;
				}

				if (std::abs(m_direction.x) != std::abs(newDirection.x)
					|| std::abs(m_direction.y) != std::abs(newDirection.y))
				{
					m_direction = newDirection;
				}
			}

			if (m_data->input.IsSpriteClicked(m_level1, sf::Mouse::Left,
				m_data->window))
			{
				m_isLevel1Clicked = true;
				m_isLevel2Clicked = false;
				m_isLevel3Clicked = false;
				m_isLevel4Clicked = false;
				m_isLevel5Clicked = false;
			}

			else if (m_data->input.IsSpriteClicked(m_level2, sf::Mouse::Left,
				m_data->window))
			{
				m_isLevel1Clicked = false;
				m_isLevel2Clicked = true;
				m_isLevel3Clicked = false;
				m_isLevel4Clicked = false;
				m_isLevel5Clicked = false;
			}

			else if (m_data->input.IsSpriteClicked(m_level3, sf::Mouse::Left,
				m_data->window))
			{
				m_isLevel1Clicked = false;
				m_isLevel2Clicked = false;
				m_isLevel3Clicked = true;
				m_isLevel4Clicked = false;
				m_isLevel5Clicked = false;
			}

			else if (m_data->input.IsSpriteClicked(m_level4, sf::Mouse::Left,
				m_data->window))
			{
				m_isLevel1Clicked = false;
				m_isLevel2Clicked = false;
				m_isLevel3Clicked = false;
				m_isLevel4Clicked = true;
				m_isLevel5Clicked = false;
			}

			else if (m_data->input.IsSpriteClicked(m_level5, sf::Mouse::Left,
				m_data->window))
			{
				m_isLevel1Clicked = false;
				m_isLevel2Clicked = false;
				m_isLevel3Clicked = false;
				m_isLevel4Clicked = false;
				m_isLevel5Clicked = true;
			}

			if (m_isLevel1Clicked)
			{
				level = 1;
			}
			else if (m_isLevel2Clicked)
			{
				level = 2;
			}
			else if (m_isLevel3Clicked)
			{
				level = 3;
			}
			else if (m_isLevel4Clicked)
			{
				level = 4;
			}
			else if (m_isLevel5Clicked)
			{
				level = 5;
			}

			if (m_isclassicButtonClicked)
			{
				gamemode = "CLASSIC";
			}
			else if (m_ismodernButtonClicked)
			{
				gamemode = "MODERN";
			}
		}
	}

	void GameplayState::Update(float dt)
	{
		m_level.setCharacterSize(25);
		m_level.setString("LEVEL:" + std::to_string(level));

		m_gamemode.setCharacterSize(25);
		m_gamemode.setString("GAMEMODE:" + gamemode);
		if (!m_isPaused)
		{
			m_elapsedTime += dt;

			switch (level)
			{
			case 1:
				m_snakeSpeed = 0.185;
				break;
			case 2:
				m_snakeSpeed = 0.125;
				break;
			case 3:
				m_snakeSpeed = 0.075;
				break;
			case 4:
				m_snakeSpeed = 0.045;
				break;
			case 5:
				m_snakeSpeed = 0.025;
				break;
			default:
				break;
			}

			if (m_elapsedTime > m_snakeSpeed)
			{
				if (m_isplayButtonClicked)
				{
					if (gamemode == "MODERN")
					{
						for (auto& wall : m_walls)
						{
							if (m_snake.IsOn(wall))
							{
								sf::sleep(sf::milliseconds(1000));
								m_data->states.AddState(StateRef(new GameOverState(m_data)), true);
								break;
							}
						}
					}

					if (gamemode == "CLASSIC")
					{
						for (auto& wall : m_walls)
						{
							if (m_snake.IsOn(wall))
							{
								m_snake.SpecialMove(m_direction);
							}
						}
					}

					if (m_snake.IsOn(m_food))
					{
						m_snake.Grow(m_direction);

						m_food.setPosition(rand() % (GAME_FRAME_WIDTH - 32 - 16 + 1) + 16,
							rand() % (GAME_FRAME_HEIGHT - 32 - 16 + 1) + 16);

						m_score += 1;
						m_scoreText.setString("SCORE: " + std::to_string(m_score));
					}
					else
					{
						m_snake.Move(m_direction);
					}

					if (m_snake.IsSelfCollision())
					{
						sf::sleep(sf::milliseconds(1000));
						m_data->states.AddState(StateRef(new GameOverState(m_data)), true);
					}

					m_elapsedTime = 0.0f;
				}
			}
		}


		sf::Event event;
		if (!m_isclassicButtonClicked)
		{
			m_classicButton.setOutlineColor(sf::Color::White);
			m_classicButton.setOutlineThickness(0);
			m_classicButton.setCharacterSize(35);
			while (m_data->window.pollEvent(event))
				if (sf::Event::MouseMoved == event.type)
				{
					if (m_classicButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
					{
						m_classicButton.setFillColor(sf::Color::Yellow);
					}
					else
					{
						m_classicButton.setFillColor(sf::Color::White);
					}
				}
		}

		if (!m_ismodernButtonClicked)
		{
			m_modernButton.setOutlineColor(sf::Color::White);
			m_modernButton.setOutlineThickness(0);;
			m_modernButton.setCharacterSize(35);
			while (m_data->window.pollEvent(event))
				if (sf::Event::MouseMoved == event.type)
				{
					if (m_backButton.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
					{
						m_backButton.setFillColor(sf::Color::Yellow);
					}
					else
					{
						m_backButton.setFillColor(sf::Color::White);
					}
				}
		}


		if (!m_isLevel1Clicked)
		{
			m_level1.setPosition((SCREEN_WIDTH / 2) - 230.0f, (SCREEN_HEIGHT / 2) -
				(m_level1.getGlobalBounds().height / 2) + 220.0f);
			m_level1.setScale(1.0f, 1.0f);
			while (m_data->window.pollEvent(event))
				if (sf::Event::MouseMoved == event.type)
				{
					if (m_level1.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
					{
						m_level1.setColor(sf::Color::Yellow);
					}
					else
					{
						m_level1.setColor(sf::Color::White);
					}
				}

		}

		if (!m_isLevel2Clicked)
		{
			m_level2.setPosition((SCREEN_WIDTH / 2) - 150.0f, (SCREEN_HEIGHT / 2) -
				(m_level2.getGlobalBounds().height / 2) + 220.0f);
			m_level2.setScale(1.0f, 1.0f);
			while (m_data->window.pollEvent(event))
				if (sf::Event::MouseMoved == event.type)
				{
					if (m_level2.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
					{
						m_level2.setColor(sf::Color::Yellow);
					}
					else
					{
						m_level2.setColor(sf::Color::White);
					}
				}

		}

		if (!m_isLevel3Clicked)
		{
			m_level3.setPosition((SCREEN_WIDTH / 2) - 70.0f, (SCREEN_HEIGHT / 2) -
				(m_level3.getGlobalBounds().height / 2) + 220.0f);
			m_level3.setScale(1.0f, 1.0f);
			while (m_data->window.pollEvent(event))
				if (sf::Event::MouseMoved == event.type)
				{
					if (m_level3.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
					{
						m_level3.setColor(sf::Color::Yellow);
					}
					else
					{
						m_level3.setColor(sf::Color::White);
					}
				}

		}

		if (!m_isLevel4Clicked)
		{
			m_level4.setPosition((SCREEN_WIDTH / 2) + 10.0f, (SCREEN_HEIGHT / 2) -
				(m_level4.getGlobalBounds().height / 2) + 220.0f);
			m_level4.setScale(1.0f, 1.0f);
			while (m_data->window.pollEvent(event))
				if (sf::Event::MouseMoved == event.type)
				{
					if (m_level4.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
					{
						m_level4.setColor(sf::Color::Yellow);
					}
					else
					{
						m_level4.setColor(sf::Color::White);
					}
				}

		}

		if (!m_isLevel5Clicked)
		{
			m_level5.setPosition((SCREEN_WIDTH / 2) + 90.0f, (SCREEN_HEIGHT / 2) -
				(m_level5.getGlobalBounds().height / 2) + 220.0f);
			m_level5.setScale(1.0f, 1.0f);
			while (m_data->window.pollEvent(event))
				if (sf::Event::MouseMoved == event.type)
				{
					if (m_level5.getGlobalBounds().contains(
						sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
					{
						m_level5.setColor(sf::Color::Yellow);
					}
					else
					{
						m_level5.setColor(sf::Color::White);
					}
				}
		}

		if (m_isLevel1Clicked)
		{
			m_level1.setColor(sf::Color::Yellow);
			m_level1.setPosition((SCREEN_WIDTH / 2) - 231.2f, (SCREEN_HEIGHT / 2) -
				(m_level1.getGlobalBounds().height / 2) + 218.8f);
			m_level1.setScale(1.2f, 1.2f);

		}

		if (m_isLevel2Clicked)
		{
			m_level2.setColor(sf::Color::Yellow);
			m_level2.setPosition((SCREEN_WIDTH / 2) - 151.2f, (SCREEN_HEIGHT / 2) -
				(m_level2.getGlobalBounds().height / 2) + 218.8f);
			m_level2.setScale(1.2f, 1.2f);

		}

		if (m_isLevel3Clicked)
		{
			m_level3.setColor(sf::Color::Yellow);
			m_level3.setPosition((SCREEN_WIDTH / 2) - 71.2f, (SCREEN_HEIGHT / 2) -
				(m_level3.getGlobalBounds().height / 2) + 218.8f);
			m_level3.setScale(1.2f, 1.2f);

		}

		if (m_isLevel4Clicked)
		{
			m_level4.setColor(sf::Color::Yellow);
			m_level4.setPosition((SCREEN_WIDTH / 2) + 8.8f, (SCREEN_HEIGHT / 2) -
				(m_level4.getGlobalBounds().height / 2) + 218.8f);
			m_level4.setScale(1.2f, 1.2f);

		}

		if (m_isLevel5Clicked)
		{
			m_level5.setColor(sf::Color::Yellow);
			m_level5.setPosition((SCREEN_WIDTH / 2) + 88.8f, (SCREEN_HEIGHT / 2) -
				(m_level5.getGlobalBounds().height / 2) + 218.8f);
			m_level5.setScale(1.2f, 1.2f);
			;
		}


		if (m_isclassicButtonClicked)
		{
			m_classicButton.setFillColor(sf::Color::Yellow);
			m_classicButton.setOutlineColor(sf::Color::Red);
			m_classicButton.setCharacterSize(36);
			m_classicButton.setOutlineThickness(0.5);
		}

		if (m_ismodernButtonClicked)
		{
			m_modernButton.setFillColor(sf::Color::Yellow);
			m_modernButton.setOutlineColor(sf::Color::Red);
			m_modernButton.setCharacterSize(36);
			m_modernButton.setOutlineThickness(0.5);
		}

	}

	void GameplayState::Draw(float dt)
	{
		m_data->window.clear();

		m_data->window.draw(m_background);

		if (!m_isplayButtonClicked)
		{
			m_data->window.draw(m_title);
			m_data->window.draw(m_classicButton);
			m_data->window.draw(m_modernButton);
			m_data->window.draw(m_backButton);

			m_data->window.draw(m_levelButton);
			m_data->window.draw(m_level1);
			m_data->window.draw(m_level2);
			m_data->window.draw(m_level3);
			m_data->window.draw(m_level4);
			m_data->window.draw(m_level5);

			if ((m_isclassicButtonClicked && (m_isLevel1Clicked || m_isLevel2Clicked
				|| m_isLevel3Clicked || m_isLevel4Clicked || m_isLevel5Clicked)) ||
				(m_ismodernButtonClicked && (m_isLevel1Clicked || m_isLevel2Clicked
					|| m_isLevel3Clicked || m_isLevel4Clicked || m_isLevel5Clicked)))
			{
				m_data->window.draw(m_playButton);
			}
		}

		else if (m_isplayButtonClicked)
		{
			m_data->window.draw(m_grass);

			for (auto& wall : m_walls)
			{
				m_data->window.draw(wall);
			}

			m_data->window.draw(m_food);
			m_data->window.draw(m_snake);
			m_data->window.draw(m_scoreText);
			m_data->window.draw(m_level);
			m_data->window.draw(m_gamemode);
		}

		m_data->window.display();
	}

	void GameplayState::Pause()
	{
		m_isPaused = true;
	}

	void GameplayState::Resume()
	{
		m_isPaused = false;
	}
}
