#include <Sound.hpp>
#include <DEFINITIONS.hpp>

Sound::Sound() {
    m_clickSound.setBuffer(m_clickSoundBuffer);
    m_moveSound.setBuffer(m_moveSoundBuffer);
    m_eatSound.setBuffer(m_eatSoundBuffer);
    m_hitSound.setBuffer(m_hitSoundBuffer);
    m_gameoverSound.setBuffer(m_gameoverSoundBuffer);
}

bool Sound::loadSounds() {
    bool success = true;

    if (!m_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH)) {
        std::cout << "Error loading hit sound" << std::endl;
        success = false;
    }

    if (!m_backgroundMusic.openFromFile(BACKGROUND_SOUND_FILEPATH)) {
        std::cout << "Error loading background music" << std::endl;
        success = false;
    }

    if (!m_gameoverSoundBuffer.loadFromFile(GAMEOVER_SOUND_FILEPATH)) {
        std::cout << "Error loading game over sound" << std::endl;
        success = false;
    }

    if (!m_clickSoundBuffer.loadFromFile(BUTTON_CLICK_SOUND_FILEPATH)) {
        std::cout << "Error loading click sound" << std::endl;
        success = false;
    }

    if (!m_eatSoundBuffer.loadFromFile(EAT_FOOD_SOUND_FILEPATH)) {
        std::cout << "Error loading eat sound" << std::endl;
        success = false;
    }

    if (!m_moveSoundBuffer.loadFromFile(SNAKE_MOVE_SOUND_FILEPATH)) {
        std::cout << "Error loading move sound" << std::endl;
        success = false;
    }

    return success;
}

void Sound::playBackgroundMusic() {
    m_backgroundMusic.setLoop(true);
    m_backgroundMusic.play();
}

void Sound::stopAllSounds() {
    m_clickSound.stop();
    m_moveSound.stop();
    m_eatSound.stop();
    m_hitSound.stop();
    m_gameoverSound.stop();
    m_backgroundMusic.stop();
}