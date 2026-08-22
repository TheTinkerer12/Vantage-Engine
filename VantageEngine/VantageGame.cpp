#include "VantageGame.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VantageUtilities.h"
#include "../glad/glad.h"


void VantageGame::render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    objectShader.use();

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

    objectShader.setMat4("view", view);
    objectShader.setMat4("projection", projection);

    for (int i = 0; i < sceneObjects.size(); i++)
    {
        objectShader.setMat4("model", sceneObjects[i]->transform);
        glBindVertexArray(models[sceneObjects[i]->modelIndex].VAO);
        glDrawArrays(GL_TRIANGLES, 0, models[sceneObjects[i]->modelIndex].vertexCount);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void VantageGame::mouse_callback(GLFWwindow* window, double newx, double newy)
{
    onCursorMoved(newx, newy);

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void VantageGame::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS){
        onMouseButtonPressed(button);
    }
    if (action == GLFW_RELEASE)
    {
        onMouseButtonReleased(button);
    }
}

void VantageGame::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    onCursorScrolled(xoffset, yoffset);
}

void VantageGame::static_mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    auto* instance = static_cast<VantageGame*>(glfwGetWindowUserPointer(window));
    if (instance) {
        instance->mouse_callback(window, xpos, ypos);
    }
}

void VantageGame::static_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    auto* instance = static_cast<VantageGame*>(glfwGetWindowUserPointer(window));
    if (instance) {
        instance->scroll_callback(window, xoffset, yoffset);
    }
}

void VantageGame::static_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    auto* instance = static_cast<VantageGame*>(glfwGetWindowUserPointer(window));
    if (instance) {
        instance->mouse_button_callback(window, button, action, mods);
    }
}

void VantageGame::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void VantageGame::loadModel(const char *filePath, const char *name)
{
    models.push_back(VantageUtilities::loadModel(filePath, name));
}

void VantageGame::loadTexture(const char *imagePath, const char *name)
{
    textures.push_back(Texture(VantageUtilities::loadImage(imagePath), name));
}

int VantageGame::findModel(const char *name)
{
    int index = 0;
    for (Model model : models)
    {
        if (model.name == name)
        {
            return index;
        }
        index++;
    }
    return -1;
}

int VantageGame::findTexture(const char *name)
{
    int index = 0;
    for (Texture tex : textures)
    {
        if (tex.name == name)
        {
            return index;
        }
        index++;
    }
    return -1;
}

void VantageGame::start(const char *name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(800, 600, name, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, static_mouse_callback);
    glfwSetScrollCallback(window, static_scroll_callback);
    glfwSetMouseButtonCallback(window, static_mouse_button_callback);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    objectShader = Shader("shaders/triangle.vert", "shaders/triangle.frag");

    onStart();
    while (!glfwWindowShouldClose(window)){
        update();
    }
}

void VantageGame::update()
{
    time = glfwGetTime();
    deltaTime = time - lastFrame;
    lastFrame = time;
    if (first)
    {
        first = false;
        deltaTime = 0;
    }
    onKeyPressed();
    onUpdate();
    for (auto& gameObject : sceneObjects)
    {
        for (auto& component : gameObject->components)
        {
            component.get()->Update(deltaTime);
        }
    }
    render();
}

bool VantageGame::keyPressed(int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

VantageObject& VantageGame::spawn()
{
    sceneObjects.push_back(std::make_unique<VantageObject>());
    VantageObject &refObject = *sceneObjects.back();
    refObject.Initialize(managers);
    return refObject;
}

void VantageGame::lockCursor()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void VantageGame::unlockCursor()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}