//------------------------------------------------------------------------------
// Name of this file : Mesh.h
// Author : Jean Anquetil
// Date : 29/12/2024
//------------------------------------------------------------------------------

#ifndef MESH_H
#define MESH_H
#include <iostream>
#include <vector>
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>



//------------------------------------------------------------------------------

class MeshBase {
public:
    virtual void render() = 0;  // Méthode virtuelle pure
    virtual void arm_for_drawing() = 0;  // Méthode virtuelle pure
    virtual ~MeshBase() = default;  // Destructeur virtuel pour la suppression correcte
};

//------------------------------------------------------------------------------

template <typename VertexData>
class Mesh : public MeshBase {
public:
    Mesh();
    ~Mesh() override;

    // Configure le mesh (par exemple, initialisation des buffers, etc.)
    void setup(const VertexData& data);

    // Rendre le mesh
    void arm_for_drawing() override;
    void render() override;

private:
    GLuint _VAO, _VBO;
    std::vector<float> _vertices;
};
//------------------------------------------------------------------------------

struct TriangleData{
    std::vector<float> getVertices() const {
        return {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f
        };
    }
};

#endif
//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------