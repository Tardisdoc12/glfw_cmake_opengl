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
    if (_shaders.empty()){
        return;
    }
    for (auto& shader : _shaders){
        shader.second.~Shader();
    }
}

//------------------------------------------------------------------------------

void GraphicEngine::update()
{
    std::cout << "GraphicEngine update "<< std::endl;
}

//------------------------------------------------------------------------------

void GraphicEngine::render(GLFWwindow* window)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glfwSwapBuffers(window);
    glfwPollEvents();
 }

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------