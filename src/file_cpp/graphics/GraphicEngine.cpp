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
    _shaders[1] = std::make_unique<Shader>("shaders/screen.vert", "shaders/default.frag");

    _textures["cat"] = std::make_unique<Texture>("images/cat.jpg");
    
    _meshes["cube"].push_back(std::make_shared<Mesh3D>("models/cube.obj"));
    
    // créer un mesh de screenData:
    auto screenData = ScreenData();
    _meshes["screen"].push_back(std::make_shared<Mesh<ScreenData>>());

    // create framebuffer :
    std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(800, 600);
    _framebuffers[0] = std::move(framebuffer);

    if (!_framebuffers[0]->isComplete())
    {
        std::cerr << "Framebuffer is not complete" << std::endl;
    }
    _shaders[1]->use();
    _shaders[1]->set_single_form("Texture", "texture1");
    glUniform1i(_shaders[1]->fetch_single_uniform("Texture"), 0);

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
    glDisable(GL_CULL_FACE);
}

//------------------------------------------------------------------------------

GraphicEngine::~GraphicEngine() = default;

//------------------------------------------------------------------------------

void GraphicEngine::update()
{
    _modelMatrix = update_model_matrix(_modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    _shaders[0]->use();
    glUniformMatrix4fv(_shaders[0]->fetch_single_uniform("Model"), 1, GL_FALSE, glm::value_ptr(_modelMatrix));
}

//------------------------------------------------------------------------------

void GraphicEngine::render(GLFWwindow* window)
{
    // on dessine dans un framebuffer personnel
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    _framebuffers[0]->bind();
    glEnable(GL_DEPTH_TEST);
    _framebuffers[0]->clear();

    _shaders[0]->use();
    for (auto& pair : _meshes){
        for(auto& mesh : pair.second){
            if(pair.first == "screen"){
                continue;
            }
            _textures["cat"]->bind_texture();
            mesh->arm_for_drawing();
            mesh->render();
        }
    }

    // on dessine sur le framebuffer par défaut
    _framebuffers[0]->unbind();
    glClearColor(0.2f, 0.3f, 0.9f, 1.0f);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    _shaders[1]->use();
    glBindTexture(GL_TEXTURE_2D, _framebuffers[0]->getTexture());
    _meshes["screen"][0]->arm_for_drawing();
    _meshes["screen"][0]->render();
    
    // Swap front and back buffers
    glfwSwapBuffers(window);
    
    // Poll for and process events
    glfwPollEvents();
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------