
#ifndef VANTAGE_OBJECT_H
#define VANTAGE_OBJECT_H
#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Components/IComponent.h"
#include "Managers/IManager.h"

class VantageObject
{
public:
    int modelIndex;
    int textureIndex;
    glm::mat4 transform = glm::mat4(1);
    std::vector<std::unique_ptr<IComponent>> components;
    std::vector<std::unique_ptr<IManager>>* managers = nullptr;

    VantageObject() = default;
    VantageObject(const VantageObject&) = delete;
    VantageObject& operator=(const VantageObject&) = delete;
    VantageObject(VantageObject&&) = default;
    VantageObject& operator=(VantageObject&&) = default;

    template <typename T>
    void AddComponent()
    {
        components.push_back(std::make_unique<T>());
        auto *t = GetComponent<T>();
        t->Initialize((*this));
    }

    template <typename T>
    T* GetComponent() 
    {
        for (const auto& component : components) 
        {
            if (auto casted = dynamic_cast<T*>(component.get()))
            {
                return casted;
            }
        }
        return nullptr;
    }

    template <typename T>
    T* GetManager()
    {
        if (managers == nullptr)
        {
            return nullptr;
        }
        for (const auto& manager : *managers)
        {
            if (auto casted = dynamic_cast<T*>(manager.get()))
            {
                return casted;
            }
        }
        return nullptr;
    }

    void Initialize(std::vector<std::unique_ptr<IManager>>& gameManagers)
    {
        managers = &gameManagers;
    }
};

#endif