#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include <cmath>

Vector3::Vector3()
    : x(0), y(0), z(0)
{
}
Vector3::Vector3(float x, float y, float z)
    : x(x), y(y), z(z)
{
}
Vector3::Vector3(Vector2 vec)
    : x(vec.x), y(vec.y), z(0)
{
}
Vector3::Vector3(Vector4 vec)
    : x(vec.x), y(vec.y), z(vec.z)
{
}
float Vector3::magnitude()
{
    return std::sqrt(sqrMagnitude());
}
float Vector3::sqrMagnitude()
{
    return (x * x) + (y * y) + (z * z);
}
Vector3 Vector3::normalize()
{
    float currentMagnitude;
    currentMagnitude = magnitude();
    return Vector3(x / currentMagnitude, y / currentMagnitude, z / currentMagnitude);
}