//------------------------------------------------------------------------------
// Name of this file : MatrixFunctions.cpp
// Author : Jean Anquetil
// Date : 07/01/2025
//------------------------------------------------------------------------------

#include "../../file_h/graphics/MatrixFunctions.h"

//------------------------------------------------------------------------------

glm::mat4 create_model_matrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, translation);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}

//------------------------------------------------------------------------------

glm::mat4 update_matrix(glm::mat4 matrix, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
{
    matrix = glm::translate(matrix, translation);
    matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, scale);
    return matrix;
}

//------------------------------------------------------------------------------

glm::mat4 get_projection_matrix(float fov, float aspectRatio, float near, float far)
{
    return glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

//------------------------------------------------------------------------------

glm::mat4 get_view_matrix(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp)
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------