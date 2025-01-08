//------------------------------------------------------------------------------
// Name of this file : Mesh3D.h
// Author : Jean Anquetil
// Date : 02/01/2025
//------------------------------------------------------------------------------

#pragma once

#include "Mesh.h"

//------------------------------------------------------------------------------

class Mesh3D : public MeshBase
{
public:
    Mesh3D();
    Mesh3D(const std::string obj_path);
    ~Mesh3D() override;
    void setup(const std::string obj_path);
    void arm_for_drawing() override;
    void render() override;
private:
    GLuint _VAO, _VBO, _EBO;
    std::vector<float> _vertices;
    std::vector<unsigned int> _indices;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------