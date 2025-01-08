//------------------------------------------------------------------------------
// Name of this file : GraphicEngine.cpp
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#include "../../file_h/graphics/GraphicEngine.h"
#include "../../file_h/globals/variables.h"


using namespace globals::graphic;

//------------------------------------------------------------------------------

GraphicEngine::GraphicEngine()
{
    pipelinesCor["default"] = 0;
    pipelinesCor["screen"] = 1;

    frameBuffersCor["toBlit"] = 0;

    auto shaderProgramdefault = std::make_shared<Shader>("shaders/default.vert", "shaders/default.frag");
    auto shaderProgramscreen = std::make_shared<Shader>("shaders/screen.vert", "shaders/default.frag");
    _shaders[pipelinesCor["default"]] = std::move(shaderProgramdefault);
    _shaders[pipelinesCor["screen"]] = std::move(shaderProgramscreen);

    auto cat_texture = std::make_shared<Texture>("images/cat.jpg");
    _textures[globals::entitiesCor["cat"]] = std::move(cat_texture);
    
    _meshes[globals::entitiesCor["cat"]].push_back(std::make_shared<Mesh3D>("models/cube.obj"));
    
    // créer un mesh de screenData:
    auto screenData = ScreenData();
    _meshes[globals::entitiesCor["screen"]].push_back(std::make_shared<Mesh<ScreenData>>());

    auto catEntity = std::make_shared<Entity>(glm::vec3(0.0f, 0.0f, -1.f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    _entities[globals::entitiesCor["cat"]] = std::move(catEntity);

    _framebuffers[frameBuffersCor["toBlit"]] = std::make_shared<Framebuffer>();
    _framebuffers[frameBuffersCor["toBlit"]]->attachTexture(800, 600);
    _framebuffers[frameBuffersCor["toBlit"]]->attachRenderbuffer(800, 600);

    if (!_framebuffers[frameBuffersCor["toBlit"]]->isComplete())
    {
        std::cerr << "Framebuffer is not complete" << std::endl;
    }
    _shaders[pipelinesCor["screen"]]->use();
    _shaders[pipelinesCor["screen"]]->set_single_form("Texture", "texture1");
    glUniform1i(_shaders[pipelinesCor["screen"]]->fetch_single_uniform("Texture"), 0);

    _shaders[pipelinesCor["default"]]->use();
    _shaders[pipelinesCor["default"]]->set_single_form("Texture", "texture1");
    glUniform1i(_shaders[pipelinesCor["default"]]->fetch_single_uniform("Texture"), 0);
    
    _viewMatrix = get_view_matrix(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    _projectionMatrix = get_projection_matrix(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    
    _shaders[pipelinesCor["default"]]->set_single_form("View", "ViewMatrix");
    _shaders[pipelinesCor["default"]]->set_single_form("Projection", "ProjectionMatrix");
    _shaders[pipelinesCor["default"]]->set_single_form("Model", "ModelMatrix");
    
    glUniformMatrix4fv(_shaders[pipelinesCor["default"]]->fetch_single_uniform("View"), 1, GL_FALSE, glm::value_ptr(_viewMatrix));
    glUniformMatrix4fv(_shaders[pipelinesCor["default"]]->fetch_single_uniform("Projection"), 1, GL_FALSE, glm::value_ptr(_projectionMatrix));

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
    _entities[globals::entitiesCor["cat"]]->update_model_matrix( glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    _shaders[pipelinesCor["default"]]->use();
}

//------------------------------------------------------------------------------

void GraphicEngine::render(GLFWwindow* window)
{
    // on dessine dans un framebuffer personnel
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    _framebuffers[frameBuffersCor["toBlit"]]->bind();
    glEnable(GL_DEPTH_TEST);
    _framebuffers[frameBuffersCor["toBlit"]]->clear();

    _shaders[pipelinesCor["default"]]->use();
    
    for(auto& entity: globals::entitiesCor){
        if(entity.second == globals::entitiesCor["screen"]){
            continue;
        }
        glUniformMatrix4fv(_shaders[pipelinesCor["default"]]->fetch_single_uniform("Model"), 1, GL_FALSE, glm::value_ptr(_entities[entity.second]->get_model_matrix()));
        _textures[entity.second]->bind_texture();
        for(auto& mesh : _meshes[entity.second]){
            mesh->arm_for_drawing();
            mesh->render();
        }
    }

    // for (auto& pair : _meshes){
    //     for(auto& mesh : pair.second){
    //         if(pair.first == globals::entitiesCor["screen"]){
    //             continue;
    //         }
    //         glUniformMatrix4fv(_shaders[pipelinesCor["default"]]->fetch_single_uniform("Model"), 1, GL_FALSE, glm::value_ptr(_entities[globals::entitiesCor["cat"]]->get_model_matrix()));
    //         _textures[globals::entitiesCor["cat"]]->bind_texture();
    //         mesh->arm_for_drawing();
    //         mesh->render();
    //     }
    // }

    // on dessine sur le framebuffer par défaut
    _framebuffers[frameBuffersCor["toBlit"]]->unbind();
    glClearColor(0.2f, 0.3f, 0.9f, 1.0f);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    _shaders[pipelinesCor["screen"]]->use();
    glBindTexture(GL_TEXTURE_2D, _framebuffers[0]->getTexture());
    _meshes[globals::entitiesCor["screen"]][0]->arm_for_drawing();
    _meshes[globals::entitiesCor["screen"]][0]->render();
    
    // Swap front and back buffers
    glfwSwapBuffers(window);
    
    // Poll for and process events
    glfwPollEvents();
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------