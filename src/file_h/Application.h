//------------------------------------------------------------------------------
// Name of this file : Application.h
// Author : Jean Anquetil
// Date : 27/12/2024
//------------------------------------------------------------------------------
#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "scenes/SceneManager.h"

//------------------------------------------------------------------------------

class Application
{
public:
    Application();

    ~Application();

    void run();

private:

    float get_fps();

    void input();

    void update();

    void render();
    
    GLFWwindow* _window;
    SceneManager _sceneManager;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------