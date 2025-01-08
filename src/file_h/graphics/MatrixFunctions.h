//------------------------------------------------------------------------------
// Name of this file : MatrixFunctions.h
// Author : Jean Anquetil
// Date : 07/01/2025
//------------------------------------------------------------------------------

#pragma once

#include <iostream>
//include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//------------------------------------------------------------------------------

glm::mat4 create_model_matrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);

//------------------------------------------------------------------------------

glm::mat4 update_model_matrix(glm::mat4 modelMatrix, const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);

//------------------------------------------------------------------------------

glm::mat4 get_projection_matrix(float fov, float aspectRatio, float near, float far);

//------------------------------------------------------------------------------

glm::mat4 get_view_matrix(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp);

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------
