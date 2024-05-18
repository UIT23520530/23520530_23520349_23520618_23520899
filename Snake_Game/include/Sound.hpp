#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class Sound {
public:
    Sound();
    ~Sound() {}
    bool loadSounds();
    void playBackgroundMusic();
    void stopAllSounds();

    sf::SoundBuffer m_clickSoundBuffer;
    sf::SoundBuffer m_moveSoundBuffer;
    sf::SoundBuffer m_eatSoundBuffer;
    sf::SoundBuffer m_hitSoundBuffer;
    sf::SoundBuffer m_gameoverSoundBuffer;

    sf::Sound m_clickSound;
    sf::Sound m_moveSound;
    sf::Sound m_eatSound;
    sf::Sound m_hitSound;
    sf::Sound m_gameoverSound;
    sf::Sound m_gamemusicSound;

    sf::Music m_backgroundMusic;
};
