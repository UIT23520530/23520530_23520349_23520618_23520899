#include <HighScoreState.hpp>
#include <OptionState.hpp>
#include <DEFINITIONS.hpp>

#include <fstream>
#include <iostream>

namespace Engine
{
    HighScoreState::HighScoreState(GameDataRef data) : m_data(data) {}

    void HighScoreState::LoadHighScores()
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

    void HighScoreState::Init()
    {
        LoadHighScores();

        m_data->assets.LoadTexture("Background", GAME_BACKGROUND_FILEPATH);
        m_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
        m_data->assets.LoadFont("Highscore Title", SCORE_FONT_FILEPATH);
        m_data->assets.LoadFont("Back Button Font",
            BACK_BUTTON_FONT_FILEPATH);

        m_background.setTexture(m_data->assets.GetTexture("Background"));
        m_title.setTexture(m_data->assets.GetTexture("Game Title"));
        m_highscoreTitle.setFont(m_data->assets.GetFont("Highscore Title"));
        m_backButton.setFont(m_data->assets.GetFont("Back Button Font"));
        m_backButton.setString("BACK");
        m_backButton.setPosition(20.0f, SCREEN_HEIGHT - 40.0f);
        m_highscoreTitle.setString("HIGHSCORES");
        m_highscoreTitle.setCharacterSize(40);
        m_highscoreTitle.setFillColor(sf::Color::Cyan);
        m_highscoreTitle.setPosition((SCREEN_WIDTH / 2) - (m_highscoreTitle.getGlobalBounds().
            width / 2) - 135.0f, (SCREEN_HEIGHT / 2) - (m_highscoreTitle.getGlobalBounds().
                height / 2) - 20.0f);




        for (int i = 0; i < m_highscores.size(); ++i)
        {
            sf::Text text;
            text.setFont(m_data->assets.GetFont("Highscore Title"));
            text.setString(std::to_string(m_highscores[i]));
            text.setCharacterSize(35);
            text.setFillColor(sf::Color::Green);
            text.setPosition((SCREEN_WIDTH / 2) - (text.getGlobalBounds().width / 2) - 135.0f, 400 + i * 60);
            m_highscoreTexts.push_back(text);
        }
    }

    void HighScoreState::ProcessInput()
    {
        sf::Event event;
        while (m_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                m_data->sound.stopAllSounds();
                m_data->window.close();
            }
            if (m_data->input.IsTextClicked(m_backButton, sf::Mouse::Left,
                m_data->window))
            {
                m_data->sound.m_clickSound.play();
                m_data->states.AddState(StateRef(new OptionState(m_data)), true);
            }
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
    }

    void HighScoreState::Update(float dt) {}

    void HighScoreState::Draw(float dt)
    {
        m_data->window.clear();

        m_data->window.draw(m_background);
        m_data->window.draw(m_title);
        m_data->window.draw(m_highscoreTitle);
        m_data->window.draw(m_backButton);
        for (const auto& text : m_highscoreTexts)
        {
            m_data->window.draw(text);
        }

        m_data->window.display();
    }
}
