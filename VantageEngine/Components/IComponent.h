#ifndef ICOMPONENT_H
#define ICOMPONENT_H
#pragma once

class VantageObject;
class IComponent {
public:
    virtual ~IComponent() = default;

    virtual void Initialize(VantageObject& attached) = 0;
    virtual void Update(float deltaTime) = 0;

    virtual const char* GetName() const = 0;
};

#endif