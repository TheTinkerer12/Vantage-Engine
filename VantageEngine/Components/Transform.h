
#ifndef TRANSFORM_H
#define TRANSFORM_H
#pragma once
#include "../../VantageMath/Vectors/Vector3.h"
#include "IComponent.h"
#include "../VantageObject.h"
#include <glm/glm.hpp>

class Transform : public IComponent
{
private:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale = Vector3(1, 1, 1);
    glm::mat4 oldPosition = glm::mat4(1.0f);
    glm::mat4 oldRotation = glm::mat4(1.0f);
    glm::mat4 oldScale = glm::mat4(1.0f);
    bool positionChanged = false;
    bool rotationChanged = false;
    bool scaleChanged = false;
    VantageObject *attached = nullptr;
public:
    const char* GetName() const override
    {
        return "Transform";
    }
    void Initialize(VantageObject& attached) override
    {
        this->attached = &attached;
        positionChanged = true;
        rotationChanged = true;
        scaleChanged = true;
        Rebuild();
    }
    void Update(float deltaTime) override
    {

    }
    Vector3 GetPosition();
    void SetPosition(Vector3 position);
    Vector3 GetRotation();
    void SetRotation(Vector3 rotation);
    Vector3 GetScale();
    void SetScale(Vector3 scale);
    void Translate(Vector3 translate);
private:
    void Rebuild();
};

#endif