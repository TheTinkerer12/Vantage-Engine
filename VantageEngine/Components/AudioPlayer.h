
#ifndef AUDIO_PLAYER_H
#define AUDIO_Player_H
#pragma once
#include "../VantageObject.h"
#include "../Managers/AudioManager.h"
#include <iostream>

class AudioPlayer : public IComponent
{
private:
    sf::SoundBuffer soundBuffer;
public:
    sf::Sound sound;
    VantageObject* attached = nullptr;
    AudioManager* manager = nullptr;

    const char* GetName() const override
    {
        return "AudioPlayer";
    }

    void Initialize(VantageObject& attached) override
    {
        this->attached = &attached;
        this->manager = attached.GetManager<AudioManager>();
    }

    void Update(float deltaTime) override
    {
    }

    void PlayMusic(const char *filePath)
    {
        if (manager == nullptr)
        {
            std::cout << "AudioPlayer has no AudioManager" << std::endl;
            return;
        }
        sf::Music& music = manager->loadMusic(filePath);
        music.play();
    }

    void PlaySound(const char *filePath)
    {
        soundBuffer = manager->loadSound(filePath);
        sound.setBuffer(soundBuffer);
        sound.play();
    }
};

#endif