
#ifndef VECTOR2_H
#define VECTOR2_H
#pragma once


class Vector3;
class Vector4;
class Vector2
{
public:
    float x = 0;
    float y = 0;

    Vector2();
    Vector2(float x, float y);
    Vector2(Vector3 vec);
    Vector2(Vector4 vec);

    float magnitude();
    float sqrMagnitude();
    Vector2 normalize();
};
#endif