
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "cmath"

Vector2::Vector2()
    : x(0), y(0)
{
}
Vector2::Vector2(float x, float y)
    : x(x), y(y)
{
}
Vector2::Vector2(Vector3 vec)
    : x(vec.x), y(vec.y)
{
}
Vector2::Vector2(Vector4 vec)
    : x(vec.x), y(vec.y)
{
}
float Vector2::magnitude()
{
    return std::sqrt(sqrMagnitude());
}
float Vector2::sqrMagnitude()
{
    return (x * x) + (y * y);
}
Vector2 Vector2::normalize()
{
    float currentMagnitude;
    currentMagnitude = magnitude();
    return Vector2(x / currentMagnitude, y / currentMagnitude);
}