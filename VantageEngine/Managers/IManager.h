#ifndef IMANAGER_H
#define IMANAGER_H
#pragma once

class IManager {
public:
    virtual ~IManager() = default;
    virtual void Initialize() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual const char* GetName() const = 0;
};

#endif