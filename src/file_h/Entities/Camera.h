//------------------------------------------------------------------------------
// Name of this file : Camera.h
// Author : Jean Anquetil
// Date : 09/01/2025
//------------------------------------------------------------------------------

#pragma once
#include <glm/glm.hpp>

//------------------------------------------------------------------------------

class Camera
{
public:
    Camera();
    ~Camera();

    void set_position(glm::vec3 position);
    void set_rotation(glm::vec3 rotation);
    void set_scale(glm::vec3 scale);

    glm::vec3 get_position();
    glm::vec3 get_rotation();
    glm::vec3 get_scale();

    glm::mat4 get_view_matrix();
    void update_view_matrix(glm::vec3 move, glm::vec3 rotate, glm::vec3 rescale);

private:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

    glm::mat4 _viewMatrix;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------