
#ifndef VANTAGE_GAME_H
#define VANTAGE_GAME_H
#pragma once
#include <vector>
#include <iostream>
#include "VantageObject.h"
#include "Texture.h"
#include "Model.h"
#include "../shader.h"

class VantageGame
{
protected:
    VantageGame()
    {
        models = std::vector<Model>();
        textures = std::vector<Texture>();
        sceneObjects = std::vector<std::unique_ptr<VantageObject>>();
    }

public:
    float deltaTime = 0.0f;
    float time = 0.0f;
    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    float yaw = -90.0f;
    float pitch = 0;
    float fov = 45;
    float lastX = 400, lastY = 300;
    const char *name;

private:

    bool first = true;
    bool firstMouse = true;
    GLFWwindow* window;
    float lastFrame = 0.0f;
    Shader objectShader;
    std::vector<Model> models;
    std::vector<Texture> textures;
    std::vector<std::unique_ptr<VantageObject>> sceneObjects;


    virtual void onStart() = 0;
    virtual void onUpdate() = 0;

    void render();
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void static_mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void static_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    void loadModel(const char *filePath, const char *name);
    void loadTexture(const char *imagePath, const char *name);
    void start(const char *name);
    void update();
    bool keyPressed(int key);
    void spawn(VantageObject&& vantageObject);
    virtual void onKeyPressed() = 0;
};

#endif