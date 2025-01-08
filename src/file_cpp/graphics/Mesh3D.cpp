//------------------------------------------------------------------------------
// Name of this file : Mesh3D.cpp
// Author : Jean Anquetil
// Date : 02/01/2025
//------------------------------------------------------------------------------

#include "../../file_h/graphics/Mesh3D.h"
#define TINYOBJLOADER_IMPLEMENTATION 1
#include "tiny_obj_loader.h"
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//------------------------------------------------------------------------------

Mesh3D::Mesh3D() {
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);
}

//------------------------------------------------------------------------------

Mesh3D::Mesh3D(const std::string obj_path) {
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);
    this->setup(obj_path);
}

//------------------------------------------------------------------------------

Mesh3D::~Mesh3D() {
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);
}

//------------------------------------------------------------------------------

void Mesh3D::arm_for_drawing() {
    glBindVertexArray(_VAO);
}

//------------------------------------------------------------------------------

void Mesh3D::render() {
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
}

//------------------------------------------------------------------------------

void Mesh3D::setup(const std::string obj_path) {
    tinyobj::attrib_t attrib;  // Attributs (positions, normales, UV)
    std::vector<tinyobj::shape_t> shapes;  // Contient les formes (meshes)
    std::vector<tinyobj::material_t> materials;  // Contient les matériaux
    std::string warn, err;
    
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, obj_path.c_str());
    if (!warn.empty()) {
        std::cerr << warn << std::endl;
    }
    if (!ret){
        std::cerr << "Failed to load/parse .obj file" << std::endl;
        return;
    }
    // Traiter les attributs
        
    std::vector<std::tuple<float, float, float, float, float>> uniqueVertices;

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            float vx = attrib.vertices[3 * index.vertex_index + 0];
            float vy = attrib.vertices[3 * index.vertex_index + 1];
            float vz = attrib.vertices[3 * index.vertex_index + 2];

            float tx = 0.0f, ty = 0.0f;
            if (index.texcoord_index >= 0) {
                tx = attrib.texcoords[2 * index.texcoord_index + 0];
                ty = attrib.texcoords[2 * index.texcoord_index + 1];
            }

            std::tuple<float, float, float, float, float> vertex = std::make_tuple(vx, vy, vz, tx, ty);

            // Rechercher manuellement le sommet dans la liste des sommets uniques
            auto it = std::find(uniqueVertices.begin(), uniqueVertices.end(), vertex);

            if (it == uniqueVertices.end()) {
                // Sommet non trouvé, l'ajouter
                uniqueVertices.push_back(vertex);
                _vertices.push_back(vx);
                _vertices.push_back(vy);
                _vertices.push_back(vz);
                _vertices.push_back(tx);
                _vertices.push_back(ty);
                _indices.push_back(uniqueVertices.size() - 1);
            } else {
                // Sommet trouvé, utiliser son index
                _indices.push_back(std::distance(uniqueVertices.begin(), it));
            }
        }
    }

    // Charger les données dans les buffers
    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // UV
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
}
//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------