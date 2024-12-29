//------------------------------------------------------------------------------
// Name of this file : GraphicEngine.cpp
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#include "../../file_h/graphics/GraphicEngine.h"

//------------------------------------------------------------------------------

GraphicEngine::GraphicEngine()
{
    _shaders[0] = std::make_unique<Shader>("shaders/default.vert", "shaders/default.frag");
    auto triangleData = std::make_shared<TriangleData>();
    auto triangleMesh = std::make_shared<Mesh<TriangleData>>();
    _triangles.push_back(triangleMesh);
    glEnable(GL_DEPTH_TEST);
}

//------------------------------------------------------------------------------

GraphicEngine::~GraphicEngine(){
    if (_framebuffers.empty()){
        return;
    }
    for(auto& framebuffer : _framebuffers){
        framebuffer.second->~Framebuffer();
    }
    if (_shaders.empty()){
        return;
    }
    for (auto& shader : _shaders){
        shader.second->~Shader();
    }
}

//------------------------------------------------------------------------------

void GraphicEngine::update()
{
}

//------------------------------------------------------------------------------

void GraphicEngine::render(GLFWwindow* window)
{
    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shaders[0]->use();
    for(auto& triangle : _triangles){
        triangle->arm_for_drawing();
        triangle->render();
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------