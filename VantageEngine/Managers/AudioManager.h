
#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H
#pragma once
#include <vector>
#include <memory>
#include <string>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "IManager.h"

class AudioManager : public IManager
{
private:
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> musics;

public:
    sf::SoundBuffer loadSound(const char *filePath);
    sf::Music &loadMusic(const char *filePath);

    void Initialize() override
    {
        return;
    }
    void Update(float deltaTime) override
    {
        return;
    }
    const char* GetName() const override
    {
        return "AudioManager";
    }
};

#endif