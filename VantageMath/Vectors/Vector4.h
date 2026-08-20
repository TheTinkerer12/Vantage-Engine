
#ifndef VECTOR4_H
#define VECTOR4_H
#pragma once

class Vector2;
class Vector3;

class Vector4
{
public:
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;

    Vector4();
    Vector4(float x, float y, float z, float w);
    Vector4(Vector2 vec);
    Vector4(Vector3 vec);

    float magnitude();
    float sqrMagnitude();
    Vector4 normalize();
};
#endif