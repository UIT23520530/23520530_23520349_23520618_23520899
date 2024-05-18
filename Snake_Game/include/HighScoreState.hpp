#pragma once

#include <State.hpp>
#include <Game.hpp>
#include <vector>
#include <SFML/Graphics.hpp>

namespace Engine
{
    class HighScoreState : public State
    {
    public:
        HighScoreState(GameDataRef data);

        void Init();
        void ProcessInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataRef m_data;
        sf::Sprite m_background;
        sf::Sprite m_title;
        sf::Text m_highscoreTitle;
        std::vector<sf::Text> m_highscoreTexts;
        sf::Text m_backButton;

        std::vector<int> m_highscores;

        void LoadHighScores();
    };
}
