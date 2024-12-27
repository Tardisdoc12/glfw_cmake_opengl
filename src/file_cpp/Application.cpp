//------------------------------------------------------------------------------
// Name of this file : Application.cpp
// Author : Jean Anquetil
// Date : 27/12/2024
//------------------------------------------------------------------------------

#include "../file_h/Application.h"
#include <GLFW/glfw3.h>
#include <iostream>

//------------------------------------------------------------------------------

Application::Application()
{
    if(!glfwInit())
    {
        std::cerr << "Échec de l'initialisation de GLFW\n";
        return;
    }
    window = glfwCreateWindow(800, 600, "Fenêtre GLFW", nullptr, nullptr);
    glfwMakeContextCurrent(window);
}

//------------------------------------------------------------------------------

Application::~Application()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

//------------------------------------------------------------------------------

void Application::run()
{
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------