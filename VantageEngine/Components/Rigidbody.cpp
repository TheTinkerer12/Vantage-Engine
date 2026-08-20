
#include "Rigidbody.h"

void Rigidbody::SetGravity(Vector3 gravity)
{
    this->gravity = gravity;
}

Vector3 Rigidbody::GetGravity()
{
    return gravity;
}