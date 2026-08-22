
#include "AudioManager.h"
#include <iostream>
#include <memory>
#include <SFML/Audio.hpp>

sf::Music& AudioManager::loadMusic(const char *filePath)
{
    auto& slot = musics[filePath];
    if (!slot)
    {
        slot = std::make_unique<sf::Music>();
        if (!slot->openFromFile(filePath))
        {
            std::cout << "Error loading music from " << filePath << std::endl;
        }
    }
    return *slot;
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