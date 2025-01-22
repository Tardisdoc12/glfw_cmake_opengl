//------------------------------------------------------------------------------
// Name of this file : Camera.h
// Author : Jean Anquetil
// Date : 09/01/2025
//------------------------------------------------------------------------------

#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

//------------------------------------------------------------------------------

class Camera
{
public:
    Camera();
    Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up);
    ~Camera();

    void set_position(glm::vec3 position);

    const glm::vec3 get_position();

    void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY);

    void updateKeyboardInput(const float& dt, const int direction);

    void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY);

    const glm::mat4 get_view_matrix();
    void update_view_matrix(glm::vec3 move, glm::vec3 rotate, glm::vec3 rescale);

private:
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;

    glm::vec3 _worldUp;

    GLfloat _yaw;
    GLfloat _pitch;
    GLfloat _roll;

    GLfloat _movementSpeed;
    GLfloat _mouseSensitivity;

    glm::mat4 _viewMatrix;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------