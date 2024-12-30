//------------------------------------------------------------------------------
// Name of this file : mesh.cpp
// Author : Jean Anquetil
// Date : 29/12/2024
//------------------------------------------------------------------------------

#include "../../file_h/graphics/Mesh.h"
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>


//------------------------------------------------------------------------------

template <typename VertexData>
Mesh<VertexData>::Mesh() {
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    this->setup(VertexData());
}

//------------------------------------------------------------------------------

template <typename VertexData>
Mesh<VertexData>::~Mesh() {
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
}

//------------------------------------------------------------------------------

template<typename VertexData>
void Mesh<VertexData>::setup(const VertexData& data) {
    
    _vertices = data.getVertices();
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &_vertices[0], GL_STATIC_DRAW);

    // Configurer les attributs de vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);  // Position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));  // Texture
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

//------------------------------------------------------------------------------

template<typename VertexData>
void Mesh<VertexData>::arm_for_drawing() {
    glBindVertexArray(_VAO);
}

//------------------------------------------------------------------------------

template<typename VertexData>
void Mesh<VertexData>::render() {
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / 5);
}

//------------------------------------------------------------------------------

template class Mesh<SquareData>;

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------