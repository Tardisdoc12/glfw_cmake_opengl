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
        std::cerr << "Échec de l'initialisation de GLFW\n";
        return;
    }
    _window = glfwCreateWindow(800, 600, "Fenêtre GLFW", nullptr, nullptr);
    glfwMakeContextCurrent(_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    _sceneManager.addScene(std::make_unique<StartingScene>());
}

//------------------------------------------------------------------------------

Application::~Application()
{
    _sceneManager.~SceneManager();
}

//------------------------------------------------------------------------------

void Application::input()
{
    _sceneManager.input();
}

//------------------------------------------------------------------------------

void Application::update()
{
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