//------------------------------------------------------------------------------
// Name of this file : Entity.h
// Author : Jean Anquetil
// Date : 08/01/2025
//------------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "../graphics/MatrixFunctions.h"

//------------------------------------------------------------------------------

class Entity
{

public:
    Entity();
    Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    ~Entity();

    glm::mat4 get_model_matrix() const;
    void update_model_matrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale);

private:
    glm::mat4 _modelMatrix;

};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------