
#include "Transform.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

Vector3 Transform::GetPosition()
{
    return position;
}
void Transform::SetPosition(Vector3 position)
{
    this->position = position;
    positionChanged = true;
    Rebuild();
}
void Transform::Translate(Vector3 translate)
{
    position += translate;
    positionChanged = true;
    Rebuild();
}
Vector3 Transform::GetRotation()
{
    return rotation;
}
void Transform::SetRotation(Vector3 rotation)
{
    this->rotation = rotation;
    rotationChanged = true;
    Rebuild();
}
Vector3 Transform::GetScale()
{
    return scale;
}
void Transform::SetScale(Vector3 scale)
{
    this->scale = scale;
    scaleChanged = true;
    Rebuild();
}
void Transform::Rebuild()
{
    if (positionChanged)
    {
        positionChanged = false;
        oldPosition = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
    }
    if (rotationChanged)
    {
        glm::vec3 eulerRadians = glm::radians(glm::vec3(rotation.x, rotation.y, rotation.z));
        glm::quat quatRot = glm::quat(eulerRadians);
        oldRotation = glm::mat4_cast(quatRot);
        rotationChanged = false;
    }
    if (scaleChanged)
    {
        scaleChanged = false;
        oldScale = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));
    }
    if (attached == nullptr)
    {
        return;
    }
    attached->transform = oldPosition * oldRotation * oldScale;
}