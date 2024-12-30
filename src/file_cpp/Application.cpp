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
    _lastTime = 0.0f;
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

float Application::get_dt()
{ // Temps de la dernière frame
    float currentTime = glfwGetTime(); // Temps actuel
    float dt = currentTime - _lastTime; // Calcul du delta time
    _lastTime = currentTime; // Mise à jour du temps de la dernière frame
    return dt;
}

//------------------------------------------------------------------------------

void Application::input()
{
    _sceneManager.input();
}

//------------------------------------------------------------------------------

void Application::update()
{
    float fps = get_dt();
    _sceneManager.update(fps);
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