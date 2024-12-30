//------------------------------------------------------------------------------
// Name of this file : Texture.h
// Author : Jean Anquetil
// Date : 30/12/2024
//------------------------------------------------------------------------------

#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>


//------------------------------------------------------------------------------

class Texture
{
public:
    Texture() = default;
    Texture(const std::string image_path);
    ~Texture();

    void load_texture(const std::string image_path);
    void bind_texture();
    void unbind_texture();

private:
    unsigned int _texture;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------