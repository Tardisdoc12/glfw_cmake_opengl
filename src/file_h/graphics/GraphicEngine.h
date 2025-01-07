//------------------------------------------------------------------------------
// Name of this file : GraphicEngine.h
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#pragma once
#include <iostream>
#include <map>
#include <memory>
#include "Framebuffer.h"
#include "Shader.h"
#include "Mesh.h"
//#include "Mesh3D.h"
#include "Texture.h"
#include "MatrixFunctions.h"

//------------------------------------------------------------------------------

class GraphicEngine
{
public:
    GraphicEngine();

    ~GraphicEngine();

    void update();

    void render(GLFWwindow* window);

private:
    std::map<int, std::unique_ptr<Framebuffer>> _framebuffers;
    std::map<int, std::unique_ptr<Shader> > _shaders;
    std::map<std::string, std::vector<std::shared_ptr<MeshBase>>> _meshes;
    std::map<std::string, std::unique_ptr<Texture>> _textures;
    glm::mat4 _modelMatrix;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------