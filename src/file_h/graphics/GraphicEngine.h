//------------------------------------------------------------------------------
// Name of this file : GraphicEngine.h
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#pragma once
#include <iostream>
#include <map>
#include "Framebuffer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Mesh3D.h"
#include "Texture.h"
#include "MatrixFunctions.h"
#include "../Entities/Camera.h"
#include "../Entities/Entity.h"

//------------------------------------------------------------------------------

class GraphicEngine
{
public:
    GraphicEngine();

    ~GraphicEngine();

    void update();

    void render(GLFWwindow* window);

private:

    void setup_shaders();
    void setup_textures();
    void setup_meshes();
    void setup_entities();
    void setup_framebuffers();
    void setup_single_uniformms();
    void setup_multi_uniformms();

    void draw_on_framebuffer(int to);
    void transfer_framebuffer(int from, int to);
    void draw_on_screen(int from);

    std::map<int, std::shared_ptr<Framebuffer>> _framebuffers;
    std::map<int, std::shared_ptr<Shader> > _shaders;
    std::map<int, std::shared_ptr<MeshBase>> _meshes;
    std::map<int, std::shared_ptr<Texture>> _textures;
    std::map<int, std::vector<std::shared_ptr<Entity>>> _entities;
    std::shared_ptr<Camera> _camera;
    glm::mat4 _projectionMatrix;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------