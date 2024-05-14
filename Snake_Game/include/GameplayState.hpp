#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <State.hpp>
#include <Game.hpp>
#include <Snake.hpp>

#include <array>
#include <string>

namespace Engine
{
	class GameplayState : public State
	{
	private:
		GameDataRef m_data;
		sf::Sprite m_background;
		sf::Sprite m_title;
		sf::Text m_classicButton;
		sf::Text m_modernButton;
		sf::Text m_backButton;
		sf::Text m_levelButton;
		sf::Sprite m_playButton;
		sf::Sprite m_level1;
		sf::Sprite m_level2;
		sf::Sprite m_level3;
		sf::Sprite m_level4;
		sf::Sprite m_level5;

		sf::Sprite m_grass;
		sf::Sprite m_food;
		std::array<sf::Sprite, 4> m_walls;

		Snake m_snake;
		sf::Vector2f m_direction;
		float m_elapsedTime;
		float m_snakeSpeed;

		sf::Text m_level;
		sf::Text m_gamemode;
		int level;
		std::string gamemode;

		sf::Text m_scoreText;
		int m_score;

		bool m_isPaused;

		bool m_isclassicButtonClicked;
		bool m_ismodernButtonClicked;
		bool m_isplayButtonClicked;

		bool m_isLevel1Clicked;
		bool m_isLevel2Clicked;
		bool m_isLevel3Clicked;
		bool m_isLevel4Clicked;
		bool m_isLevel5Clicked;
		
	public:
		GameplayState(GameDataRef data);

		void Init();
		void ProcessInput();
		void Update(float dt);
		void Draw(float dt);

		void Pause();
		void Resume();
	};
}
