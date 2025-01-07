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
    _textures["cat"] = std::make_unique<Texture>("images/cat.jpg");
    auto squareData = std::make_shared<SquareData>();
    auto squareMesh = std::make_shared<Mesh<SquareData>>();
    _meshes["square"].push_back(squareMesh);
    //_meshes["cube"].push_back(std::make_shared<Mesh3D>("models/cube.obj"));
    _shaders[0]->use();
    _shaders[0]->set_single_form("Texture", "texture1");
    glUniform1i(_shaders[0]->fetch_single_uniform("Texture"), 0);
    glEnable(GL_DEPTH_TEST);
}

//------------------------------------------------------------------------------

GraphicEngine::~GraphicEngine() = default;

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
    for (auto& pair : _meshes){
        for(auto& mesh : pair.second){
            
            _textures["cat"]->bind_texture();
            mesh->arm_for_drawing();
            mesh->render();
        }
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------