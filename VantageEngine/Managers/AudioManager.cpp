
#include "AudioManager.h"
#include <iostream>
#include <SFML/Audio.hpp>

sf::Music& AudioManager::loadMusic(const char *filePath)
{
    sf::Music music = sf::Music();
    if (!music.openFromFile(filePath))
    {
        std::cout << "Error loading music from " << filePath << std::endl;
    }
    return music;
}
sf::SoundBuffer AudioManager::loadSound(const char *filePath)
{
    sf::SoundBuffer buf;
    if (!buf.loadFromFile(filePath))
    {
        std::cout << "Error loading sound from " << filePath << std::endl;
    }
    return buf;
}