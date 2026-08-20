
#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#pragma once
#include "../../VantageMath/Vectors/Vector3.h"
#include "../VantageObject.h"
#include "Transform.h"

class Rigidbody : public IComponent
{
public:
    VantageObject *attached = nullptr;
    Transform *trans = nullptr;
    Vector3 velocity;
    Vector3 gravity;
    const char* GetName() const override
    {
        return "Rigidbody";
    }

    void Initialize(VantageObject& attached) override
    {
        this->attached = &attached;
        this->trans = attached.GetComponent<Transform>();
    }

    void Update(float deltaTime) override
    {
        velocity += (gravity * deltaTime);
        trans->Translate(velocity * deltaTime);
    }

    void SetGravity(Vector3 gravity);
    Vector3 GetGravity();
};

#endif