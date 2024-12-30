//------------------------------------------------------------------------------
// Name of this file : Scene.h
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//------------------------------------------------------------------------------

class SceneManager;

//------------------------------------------------------------------------------

class Scene
{
public:

    virtual ~Scene() = default;

    virtual void input() = 0;

    virtual void update(SceneManager* sceneManager, float fps) = 0;

    virtual void render(GLFWwindow* window) = 0;

    virtual void on_Enter() = 0;

    virtual void on_Exit() = 0;
private:
    // GraphicEngine _graphicEngine;
    // PhysicsEngine _physicsEngine;
    // AudioEngine _audioEngine;
    // InputEngine _inputEngine;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------