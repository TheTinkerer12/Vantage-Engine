

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
#include "VantageEngine/Components/Transform.h"
#include "VantageEngine/Components/Rigidbody.h"

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

        VantageObject physicsObject;
        physicsObject.modelIndex = 0;
        physicsObject.textureIndex = 0;

        physicsObject.AddComponent<Transform>();
        physicsObject.AddComponent<Rigidbody>();

        Rigidbody* rb = physicsObject.GetComponent<Rigidbody>();
        (*rb).SetGravity(Vector3(0, -9.81f, 0));


        VantageObject refObject;
        refObject.modelIndex = 0;
        refObject.textureIndex = 0;
        
        spawn(std::move(physicsObject));
        spawn(std::move(refObject));
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