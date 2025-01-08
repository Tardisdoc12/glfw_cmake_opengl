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
    //auto squareData = std::make_shared<SquareData>();
    //auto squareMesh = std::make_shared<Mesh<SquareData>>();
    //_meshes["square"].push_back(squareMesh);
    _meshes["cube"].push_back(std::make_shared<Mesh3D>("models/cube.obj"));
    _shaders[0]->use();
    _shaders[0]->set_single_form("Texture", "texture1");
    glUniform1i(_shaders[0]->fetch_single_uniform("Texture"), 0);
    
    _modelMatrix = get_model_matrix(glm::vec3(0.0f, 0.0f, -1.f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    _viewMatrix = get_view_matrix(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    _projectionMatrix = get_projection_matrix(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    
    _shaders[0]->set_single_form("View", "ViewMatrix");
    _shaders[0]->set_single_form("Projection", "ProjectionMatrix");
    _shaders[0]->set_single_form("Model", "ModelMatrix");
    
    glUniformMatrix4fv(_shaders[0]->fetch_single_uniform("View"), 1, GL_FALSE, glm::value_ptr(_viewMatrix));
    glUniformMatrix4fv(_shaders[0]->fetch_single_uniform("Projection"), 1, GL_FALSE, glm::value_ptr(_projectionMatrix));
    glUniformMatrix4fv(_shaders[0]->fetch_single_uniform("Model"), 1, GL_FALSE, glm::value_ptr(_modelMatrix));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_BLEND);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    _shaders[0]->use();
    for (auto& pair : _meshes){
        for(auto& mesh : pair.second){
            // std::cout << "Rendering mesh"<<" " << pair.first << std::endl;
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