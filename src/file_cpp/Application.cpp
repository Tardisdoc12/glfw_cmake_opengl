//------------------------------------------------------------------------------
// Name of this file : Application.cpp
// Author : Jean Anquetil
// Date : 27/12/2024
//------------------------------------------------------------------------------

#include <iostream>
#include <memory>

#include "../file_h/Application.h"

#include "../file_h/scenes/SceneManager.h"
#include "../file_h/scenes/StartingScene.h"

//------------------------------------------------------------------------------

Application::Application()
{
    if(!glfwInit())
    {
        std::cerr << "Échec de l'initialisation de GLFW ";
        return;
    }
    _window = glfwCreateWindow(800, 600, "Fenêtre GLFW", nullptr, nullptr);
    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1); // Synchronisation verticale 
    _sceneManager.addScene(std::make_unique<StartingScene>());
}

//------------------------------------------------------------------------------

Application::~Application()
{
    _sceneManager.~SceneManager();
}

//------------------------------------------------------------------------------

float Application::get_fps()
{
    static float lastTime = 0.0f;
    static int nbFrames = 0;
    static float fps = 0.0f;
    
    float currentTime = glfwGetTime();
    nbFrames++;
    if (currentTime - lastTime >= 1.0f) {
        fps = float(nbFrames) / (currentTime - lastTime);
        nbFrames = 0;
        lastTime = currentTime;
    }
    
    return fps;
}

//------------------------------------------------------------------------------

void Application::input()
{
    _sceneManager.input();
}

//------------------------------------------------------------------------------

void Application::update()
{
    float fps = get_fps();
    std::cout << "FPS : " << fps << std::endl;
    _sceneManager.update();
}

//------------------------------------------------------------------------------

void Application::render()
{
    _sceneManager.render(_window);
}

//------------------------------------------------------------------------------

void Application::run()
{
    while (!glfwWindowShouldClose(_window)) {
        this->input();

        this->update();

        this->render();
    }
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------