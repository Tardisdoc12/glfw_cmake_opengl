//------------------------------------------------------------------------------
// Name of this file : Camera.cpp
// Author : Jean Anquetil
// Date : 09/01/2025
//------------------------------------------------------------------------------

#include <glm/gtc/matrix_transform.hpp>

#include "../../file_h/Entities/Camera.h"
#include "../../file_h/graphics/MatrixFunctions.h"

//------------------------------------------------------------------------------

Camera::Camera()
{
    _position = glm::vec3(0.0f, 0.0f, 0.0f);
    _rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    _scale = glm::vec3(1.0f, 1.0f, 1.0f);
    _viewMatrix = glm::mat4(1.0f);
}

//------------------------------------------------------------------------------

Camera::~Camera() = default;

//------------------------------------------------------------------------------

void Camera::set_position(glm::vec3 position)
{
    _position = position;
}

//------------------------------------------------------------------------------

void Camera::set_rotation(glm::vec3 rotation)
{
    _rotation = rotation;
}

//------------------------------------------------------------------------------

void Camera::set_scale(glm::vec3 scale)
{
    _scale = scale;
}

//------------------------------------------------------------------------------

glm::vec3 Camera::get_position()
{
    return _position;
}

//------------------------------------------------------------------------------

glm::vec3 Camera::get_rotation()
{
    return _rotation;
}

//------------------------------------------------------------------------------

glm::vec3 Camera::get_scale()
{
    return _scale;
}

//------------------------------------------------------------------------------

glm::mat4 Camera::get_view_matrix()
{
    return _viewMatrix;
}

//------------------------------------------------------------------------------

void Camera::update_view_matrix(glm::vec3 move, glm::vec3 rotate, glm::vec3 rescale)
{
    _viewMatrix = ::update_matrix(_viewMatrix, move, rotate, rescale);
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------