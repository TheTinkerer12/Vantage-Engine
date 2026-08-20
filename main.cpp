

#include <vector>
#include "VantageEngine/VantageGame.h"

#include "VantageMath/Vectors/Vector2.h"
#include "VantageMath/Vectors/Vector3.h"
#include "VantageMath/Vectors/Vector4.h"

#include "VantageEngine/Model.h"
#include "VantageEngine/VantageUtilities.h"
#include "VantageEngine/Components/IComponent.h"
#include "VantageEngine/Texture.h"
#include "VantageEngine/VantageObject.h"
#include "VantageEngine/Transform.h"

class Spinner : public IComponent
{
public:
    VantageObject* attached = nullptr;
    const char* GetName() const override
    {
        return "TestComponent";
    }

    void Initialize(VantageObject& attached) override
    {
        this->attached = &attached;
    }

    void Update(float deltaTime) override
    {
        attached->transform = glm::translate(attached->transform, glm::vec3(0, 1 * deltaTime, 0));
    }
};

class Rigidbody : public IComponent
{
    public:
    Vector3 velocity;
    Vector3 gravity;
    VantageObject *attached = nullptr;
    Transform *trans = nullptr;
    bool init = false;
    const char* GetName() const override
    {
        return "Rigidbody";
    }

    void Initialize(VantageObject& attached) override
    {
        this->attached = &attached;
        this->trans = attached.GetComponent<Transform>();
        init = true;
    }

    void Update(float deltaTime) override
    {
        if (!init)
        {
            std::cout << "!init" << std::endl;
        }
        velocity += (gravity * deltaTime);
        trans->Translate(velocity * deltaTime);
    }

    void SetGravity(Vector3 gravity)
    {
        this->gravity = gravity;
    }

    Vector3 GetGravity()
    {
        return gravity;
    }
};

class MyGame : public VantageGame
{
    int frame;
    float totalTime;
public:
    MyGame() : VantageGame()
    {

    }
private:
    void onKeyPressed() override
    {
        float cameraSpeed = 2.5f * deltaTime;
        if (keyPressed(GLFW_KEY_LEFT_SHIFT))
        {
            cameraSpeed = 5.0 * deltaTime;
        }
        if (keyPressed(GLFW_KEY_W))
        {
            cameraPos += cameraSpeed * cameraFront;
        }
        if (keyPressed(GLFW_KEY_S))
        {
            cameraPos -= cameraSpeed * cameraFront;
        }
        if (keyPressed(GLFW_KEY_A))
        {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        if (keyPressed(GLFW_KEY_D))
        {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }
        if (keyPressed(GLFW_KEY_SPACE))
        {
            cameraPos += cameraSpeed * cameraUp;
        }
        if (keyPressed(GLFW_KEY_C))
        {
            cameraPos -= cameraSpeed * cameraUp;
        }
    }

    void onStart() override
    {
        frame = 0;
        totalTime = 0;
        loadModel("Assets/Models/test.obj", "testObject");
        loadTexture("Assets/Images/rust20_diffuse.jpg", "rust");
        VantageObject cubeObject;
        cubeObject.modelIndex = 0;
        cubeObject.textureIndex = 0;

        cubeObject.AddComponent<Transform>();

        cubeObject.AddComponent<Rigidbody>();
        Transform* trans = cubeObject.GetComponent<Transform>();

        trans->SetScale(Vector3(10, 1, 2));
        Rigidbody* rb = cubeObject.GetComponent<Rigidbody>();
        (*rb).SetGravity(Vector3(0, -9.81f, 0));
        std::cout << (*rb).GetGravity().y;
        std::cout << "|" << std::endl;

        VantageObject cubeObject2;
        cubeObject2.modelIndex = 0;
        cubeObject2.textureIndex = 0;
        
        spawn(std::move(cubeObject));
        spawn(std::move(cubeObject2));
    }

    void onUpdate() override
    {
        frame++;
        totalTime += deltaTime;
        if (totalTime > 1)
        {
            std::cout << frame / totalTime << std::endl;
            frame = 0;
            totalTime = 0;
        }
    }
};

int main()
{
    MyGame game;
    game.start("game");
}