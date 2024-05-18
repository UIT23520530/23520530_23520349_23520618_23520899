#pragma once

#include <vector>

#include <SFML/Graphics/Sprite.hpp>

#include <State.hpp>
#include <Game.hpp>

namespace Engine
{
	class GameOverState : public State
	{
	private:
		GameDataRef m_data;
		sf::Sprite m_title;
		sf::Sprite m_background;
		sf::Sprite m_gameOver;
		sf::Text m_retryButton;
		sf::Text m_exitButton;
		sf::Text m_scoreText;
		sf::Text m_highscoreText;

		sf::Text _score;
		sf::Text _best;

		int m_score;
		std::vector<int> m_highscores;

		void LoadHighScores();
		void SaveHighScores();

	public:
		GameOverState(GameDataRef data, int score);

		void Init();
		void ProcessInput();
		void Update(float dt);
		void Draw(float dt);

	};
}