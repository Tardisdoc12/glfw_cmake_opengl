//------------------------------------------------------------------------------
// Name of this file : Entity.cpp
// Author : Jean Anquetil
// Date : 08/01/2025
//------------------------------------------------------------------------------

#include "../../file_h/Entities/Entity.h"

//------------------------------------------------------------------------------

Entity::Entity()
{
    _modelMatrix = create_model_matrix(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
}

//------------------------------------------------------------------------------

Entity::Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    _modelMatrix = create_model_matrix(position, rotation, scale);
}

//------------------------------------------------------------------------------

Entity::~Entity() = default;

//------------------------------------------------------------------------------

glm::mat4 Entity::get_model_matrix() const
{
    return _modelMatrix;
}

//------------------------------------------------------------------------------

void Entity::update_model_matrix(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
{
    _modelMatrix = ::update_matrix(_modelMatrix, translation, rotation, scale);
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------