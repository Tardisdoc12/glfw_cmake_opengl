//------------------------------------------------------------------------------
// Name of this file : Camera.cpp
// Author : Jean Anquetil
// Date : 09/01/2025
//------------------------------------------------------------------------------

#include <glm/gtc/matrix_transform.hpp>

#include "../../file_h/Entities/Camera.h"
#include "../../file_h/graphics/MatrixFunctions.h"

//------------------------------------------------------------------------------

enum direction{
    FORWARD = 0,
    BACKWARD,
    LEFT,
    RIGHT
};

//------------------------------------------------------------------------------

Camera::Camera()
{
    this->_yaw = 0.f;
    this->_pitch = 0.f;
    this->_roll = 0.f;

    _position = glm::vec3(0.0f, 0.0f, 0.0f);
    _front = glm::vec3(0.0f, 0.0f, -1.0f);
    _up = glm::vec3(0.0f, 1.0f, 0.0f);
    _right = glm::normalize(glm::cross(_front, _up));
    
    _viewMatrix = ::get_view_matrix(_position, _position + _front, _up);
}

//------------------------------------------------------------------------------

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up)
{
    this->_yaw = 0.f;
    this->_pitch = 0.f;
    this->_roll = 0.f;

    _position = position;
    _front = front;
    _up = up;
    _right = glm::normalize(glm::cross(_front, _up));
    
    this->_worldUp = up;
    _viewMatrix = glm::lookAt(_position, _position + _front, _up);
}

//------------------------------------------------------------------------------

Camera::~Camera() = default;

//------------------------------------------------------------------------------

void Camera::set_position(glm::vec3 position)
{
    _position = position;
}

//------------------------------------------------------------------------------

const glm::vec3 Camera::get_position()
{
    return _position;
}

//------------------------------------------------------------------------------

const glm::mat4 Camera::get_view_matrix()
{
    return _viewMatrix;
}

//------------------------------------------------------------------------------

void Camera::update_view_matrix(glm::vec3 move, glm::vec3 rotate, glm::vec3 rescale)
{
    _viewMatrix = ::update_matrix(_viewMatrix, move, rotate, rescale);
}

//------------------------------------------------------------------------------

void Camera::updateKeyboardInput(const float& dt, const int direction)
{
    switch (direction){
        case FORWARD:
            this->_position += this->_movementSpeed * dt * this->_front;
            break;
        case BACKWARD:
            this->_position -= this->_movementSpeed * dt * this->_front;
            break;
        case LEFT:
            this->_position -= glm::normalize(glm::cross(this->_front, this->_up)) * this->_movementSpeed * dt;
            break;
        case RIGHT:
            this->_position += glm::normalize(glm::cross(this->_front, this->_up)) * this->_movementSpeed * dt;
            break;
        default:
            break;
    }
}

//------------------------------------------------------------------------------

void Camera::updateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
{
    _yaw += static_cast<GLfloat>(offsetX) * this->_mouseSensitivity * dt;
    _pitch += static_cast<GLfloat>(offsetY) * this->_mouseSensitivity * dt;

    if(_pitch > 89.0f)
        _pitch = 89.0f;
    if(_pitch < -89.0f)
        _pitch = -89.0f;

    if(_yaw > 360.0f || _yaw < -360.0f)
        _yaw = 0.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);
}

//------------------------------------------------------------------------------

void Camera::updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY)
{
    this->updateKeyboardInput(dt, direction);
    this->updateMouseInput(dt, offsetX, offsetY);
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------