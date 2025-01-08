//------------------------------------------------------------------------------
// Name of this file : GraphicEngine.cpp
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#include "../../file_h/graphics/GraphicEngine.h"
#include "../../file_h/globals/variables.h"


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
    _meshes[globals::entitiesCor["cat"]].push_back(std::make_shared<Mesh3D>("models/cube.obj"));
    
    // // créer un mesh de screenData:
    _meshes[globals::entitiesCor["screen"]].push_back(std::make_shared<Mesh<ScreenData>>());
}

//------------------------------------------------------------------------------

void GraphicEngine::setup_entities()
{
    auto catEntity = std::make_shared<Entity>(glm::vec3(0.0f, 0.0f, -1.f), glm::vec3(0.0f, 45.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    _entities[globals::entitiesCor["cat"]].push_back(std::move(catEntity));
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

    _viewMatrix = get_view_matrix(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    _projectionMatrix = get_projection_matrix(45.0f, static_cast<float>(globals::SCREEN_WIDTH) / static_cast<float>(globals::SCREEN_HEIGHT), 0.1f, 100.0f);
    glUniformMatrix4fv(_shaders[pipelinesCor["default"]]->fetch_single_uniform("View"), 1, GL_FALSE, glm::value_ptr(_viewMatrix));
    glUniformMatrix4fv(_shaders[pipelinesCor["default"]]->fetch_single_uniform("Projection"), 1, GL_FALSE, glm::value_ptr(_projectionMatrix));
}

//------------------------------------------------------------------------------

void GraphicEngine::setup_multi_uniformms()
{
}

//------------------------------------------------------------------------------

GraphicEngine::GraphicEngine()
{
    pipelinesCor["default"] = 0;
    pipelinesCor["screen"] = 1;
    frameBuffersCor["toBlit"] = 0;

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
        _textures[entity.second]->bind_texture();
        int entityID = 0;
        for(auto& mesh : _meshes[entity.second]){
            auto entiti = _entities[entity.second][entityID];
            glUniformMatrix4fv(_shaders[pipelinesCor["default"]]->fetch_single_uniform("Model"), 1, GL_FALSE, glm::value_ptr( entiti->get_model_matrix()));
            mesh->arm_for_drawing();
            mesh->render();
            entityID++;
        }
    }

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