//------------------------------------------------------------------------------
// Name of this file : Application.cpp
// Author : Jean Anquetil
// Date : 27/12/2024
//------------------------------------------------------------------------------
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
    glfwDestroyWindow(_window);
    glfwTerminate();
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
    _sceneManager.render();
}

//------------------------------------------------------------------------------

void Application::run()
{
    while (!glfwWindowShouldClose(_window)) {
        this->input();

        this->update();
        std::cout << "Application run\n"<< std::endl;
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        std::cout << "choix de la couleurs"<< std::endl;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        std::cout << "nettoyage du buffer"<< std::endl;
        this->render();
        std::cout << "affichage de la scene"<< std::endl;
        glfwSwapBuffers(_window);
        std::cout << "swap des buffers"<< std::endl;
        glfwPollEvents();
        std::cout << "poll des events\n"<< std::endl;
    }
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------