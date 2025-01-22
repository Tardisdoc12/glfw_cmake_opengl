//------------------------------------------------------------------------------
// Name of this file : GraphicEngine.cpp
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#include "../../file_h/graphics/GraphicEngine.h"
#include "../../file_h/globals/variables.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

using namespace globals::graphic;

//------------------------------------------------------------------------------

void GraphicEngine::setup_shaders()
{
    auto shaderProgramdefault = std::make_shared<Shader>("shaders/default.vert", "shaders/default.frag");
    auto shaderProgramscreen = std::make_shared<Shader>("shaders/screen.vert", "shaders/default.frag");
    _shaders[pipelinesCor["default"]] = std::move(shaderProgramdefault);
    _shaders[pipelinesCor["screen"]] = std::move(shaderProgramscreen);
}

//------------------------------------------------------------------------------

void GraphicEngine::setup_textures()
{
    auto cat_texture = std::make_shared<Texture>("images/cat.jpg");
    _textures[globals::entitiesCor["cat"]] = std::move(cat_texture);
}

//------------------------------------------------------------------------------

void GraphicEngine::setup_meshes()
{
    _meshes[globals::entitiesCor["cat"]] = std::make_shared<Mesh3D>("models/cube.obj");
    
    // // créer un mesh de screenData:
    _meshes[globals::entitiesCor["screen"]] = std::make_shared<Mesh<ScreenData>>();
}

//------------------------------------------------------------------------------

void GraphicEngine::setup_entities()
{
    auto catEntity = std::make_shared<Entity>(glm::vec3(0.0f, 0.0f, -1.f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    _entities[globals::entitiesCor["cat"]].push_back(std::move(catEntity));

    // Camera
    auto camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    _camera = std::make_shared<Camera>(camera);
}

//------------------------------------------------------------------------------

void GraphicEngine::setup_framebuffers()
{
    _framebuffers[frameBuffersCor["toBlit"]] = std::make_shared<Framebuffer>();
    _framebuffers[frameBuffersCor["toBlit"]]->attachTexture(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);
    _framebuffers[frameBuffersCor["toBlit"]]->attachRenderbuffer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);
    if (!_framebuffers[frameBuffersCor["toBlit"]]->isComplete())
    {
        std::cerr << "Framebuffer is not complete" << std::endl;
    }

    _framebuffers[frameBuffersCor["default"]] = nullptr;
}


//------------------------------------------------------------------------------

void GraphicEngine::setup_single_uniformms()
{
    _shaders[pipelinesCor["screen"]]->use();
    _shaders[pipelinesCor["screen"]]->set_single_form("Texture", "texture1");
    glUniform1i(_shaders[pipelinesCor["screen"]]->fetch_single_uniform("Texture"), 0);

    _shaders[pipelinesCor["default"]]->use();
    _shaders[pipelinesCor["default"]]->set_single_form("Texture", "texture1");
    glUniform1i(_shaders[pipelinesCor["default"]]->fetch_single_uniform("Texture"), 0);

    _shaders[pipelinesCor["default"]]->set_single_form("View", "ViewMatrix");
    _shaders[pipelinesCor["default"]]->set_single_form("Projection", "ProjectionMatrix");
    _shaders[pipelinesCor["default"]]->set_single_form("Model", "ModelMatrix");

    _projectionMatrix = get_projection_matrix(45.0f, static_cast<float>(globals::SCREEN_WIDTH) / static_cast<float>(globals::SCREEN_HEIGHT), 0.1f, 100.0f);
    glUniformMatrix4fv(_shaders[pipelinesCor["default"]]->fetch_single_uniform("Projection"), 1, GL_FALSE, glm::value_ptr(_projectionMatrix));
}

//------------------------------------------------------------------------------

void GraphicEngine::setup_multi_uniformms()
{
    // pour l'instant aucune lumière ou autre type de multi uniforms possible
}

//------------------------------------------------------------------------------

GraphicEngine::GraphicEngine()
{
    pipelinesCor["default"] = 0;
    pipelinesCor["screen"] = 1;

    frameBuffersCor["default"] = 0;
    frameBuffersCor["toBlit"] = 1;

    // All initialization functions
    setup_shaders();
    setup_textures();
    setup_meshes();
    setup_entities();
    setup_framebuffers();
    setup_single_uniformms();
    setup_multi_uniformms();

    // OpenGL options
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
    _entities[globals::entitiesCor["cat"]][0]->update_model_matrix( glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));


    // _camera->updateInput(dt, direction, offsetX, offsetY);
}

//------------------------------------------------------------------------------

void GraphicEngine::draw_on_framebuffer(int to)
{
    _framebuffers[to]->bind();
    glEnable(GL_DEPTH_TEST);
    _framebuffers[to]->clear();

    _shaders[pipelinesCor["default"]]->use();
    
    for(auto& entity_pair: _entities){
        if(entity_pair.first == globals::entitiesCor["screen"]){
            continue;
        }
        
        _textures[entity_pair.first]->bind_texture();
        auto mesh = _meshes[entity_pair.first];
        
        for(auto& entity : entity_pair.second){
            glUniformMatrix4fv(
                _shaders[pipelinesCor["default"]]->fetch_single_uniform("Model"),
                1,
                GL_FALSE,
                glm::value_ptr( entity->get_model_matrix())
            );
            mesh->arm_for_drawing();
            mesh->render();
        }
    }

    _framebuffers[to]->unbind();
    glDisable(GL_DEPTH_TEST);
}

//------------------------------------------------------------------------------

void GraphicEngine::transfer_framebuffer(int from, int to)
{
    _framebuffers[to]->bind();
    _shaders[pipelinesCor["screen"]]->use();
    glBindTexture(GL_TEXTURE_2D, _framebuffers[from]->getTexture());
    _meshes[globals::entitiesCor["screen"]]->arm_for_drawing();
    _meshes[globals::entitiesCor["screen"]]->render();
    _framebuffers[to]->unbind();
}

//------------------------------------------------------------------------------

void GraphicEngine::draw_on_screen(int from)
{
    glClearColor(0.2f, 0.3f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    _shaders[pipelinesCor["screen"]]->use();
    glBindTexture(GL_TEXTURE_2D, _framebuffers[from]->getTexture());
    _meshes[globals::entitiesCor["screen"]]->arm_for_drawing();
    _meshes[globals::entitiesCor["screen"]]->render();
}

//------------------------------------------------------------------------------

void GraphicEngine::render(GLFWwindow* window)
{
    glUniformMatrix4fv(_shaders[pipelinesCor["default"]]->fetch_single_uniform("View"), 1, GL_FALSE, glm::value_ptr(_camera->get_view_matrix()));
    
    // on dessine dans un framebuffer personnel
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    this->draw_on_framebuffer(frameBuffersCor["toBlit"]);

    int last_framebuffer = frameBuffersCor["toBlit"];
    // on transfère le framebuffer personnel sur le framebuffer par défaut
    for(auto& frambuffersID : frameBuffersCor){
        if((frambuffersID.second != frameBuffersCor["toBlit"]) && (frambuffersID.second != frameBuffersCor["default"])){
            this->transfer_framebuffer(last_framebuffer, frambuffersID.second);
            last_framebuffer = frambuffersID.second;
        }
    
    }

    // on dessine le framebuffer par défaut sur l'écran
    this->draw_on_screen(last_framebuffer);

    // Swap front and back buffers
    glfwSwapBuffers(window);
    
    // Poll for and process events
    glfwPollEvents();
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------
