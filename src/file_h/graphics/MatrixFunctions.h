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

glm::mat4 get_model_matrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);