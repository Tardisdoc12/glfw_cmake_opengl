//------------------------------------------------------------------------------
// Name of this file : GraphicEngine.cpp
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#include "../../file_h/graphics/GraphicEngine.h"

//------------------------------------------------------------------------------

GraphicEngine::GraphicEngine()
{

}

//------------------------------------------------------------------------------

GraphicEngine::~GraphicEngine(){
    if (_framebuffers.empty()){
        return;
    }
    for(auto& framebuffer : _framebuffers){
        framebuffer.second.~Framebuffer();
    }
}

//------------------------------------------------------------------------------

void GraphicEngine::update()
{
    std::cout << "GraphicEngine update\n"<< std::endl;
}

//------------------------------------------------------------------------------

void GraphicEngine::render(GLFWwindow* window)
{
    std::cout << "Application run\n"<< std::endl;
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    std::cout << "choix de la couleurs"<< std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::cout << "nettoyage du buffer"<< std::endl;
    std::cout << "GraphicEngine render\n"<< std::endl;

     std::cout << "affichage de la scene"<< std::endl;
    glfwSwapBuffers(window);
    std::cout << "swap des buffers"<< std::endl;
    glfwPollEvents();
    std::cout << "poll des events\n"<< std::endl;
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------