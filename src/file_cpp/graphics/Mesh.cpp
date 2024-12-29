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

Triangle::Triangle()
{
    _vertices = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &_vertices[0], GL_STATIC_DRAW);

    // Attribut de position (aPos)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Attribut de couleur (aColor)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

//------------------------------------------------------------------------------

Triangle::~Triangle()
{
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
}

//------------------------------------------------------------------------------

void Triangle::arm_for_drawing()
{
    glBindVertexArray(_VAO);
}

//------------------------------------------------------------------------------

void Triangle::render()
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------