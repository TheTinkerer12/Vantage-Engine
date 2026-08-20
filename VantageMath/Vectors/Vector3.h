
#ifndef VECTOR3_H
#define VECTOR3_H
#pragma once

class Vector2;
class Vector4;

class Vector3
{
public:
    float x = 0;
    float y = 0;
    float z = 0;

    Vector3();
    Vector3(float x, float y, float z);
    Vector3(Vector2 vec);
    Vector3(Vector4 vec);

    float magnitude();
    float sqrMagnitude();
    Vector3 normalize();

    Vector3 operator*(const Vector3& other) const
    {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    Vector3& operator*=(const Vector3& other)
    {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;
        return *this;
    }

    Vector3 operator*(const float& other) const
    {
        return Vector3(x * other, y * other, z * other);
    }

    Vector3& operator*=(const float& other)
    {
        this->x *= other;
        this->y *= other;
        this->z *= other;
        return *this;
    }

    Vector3 operator+(const Vector3& other) const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3& operator+=(const Vector3& other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }
};
#endif