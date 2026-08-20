#include "Vector4.h"
#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

Vector4::Vector4()
    : x(0), y(0), z(0), w(0)
{
}
Vector4::Vector4(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w)
{
}
Vector4::Vector4(Vector2 vec)
    : x(vec.x), y(vec.y), z(0), w(0)
{
}
Vector4::Vector4(Vector3 vec)
    : x(vec.x), y(vec.y), z(vec.z), w(0)
{
}
float Vector4::magnitude()
{
    return std::sqrt(sqrMagnitude());
}
float Vector4::sqrMagnitude()
{
    return (x * x) + (y * y) + (z * z) + (w * w);
}
Vector4 Vector4::normalize()
{
    float currentMagnitude;
    currentMagnitude = magnitude();
    return Vector4(x / currentMagnitude, y / currentMagnitude, z / currentMagnitude, w / currentMagnitude);
}