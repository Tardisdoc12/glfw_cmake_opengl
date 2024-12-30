//------------------------------------------------------------------------------
// Name of this file : Texture.cpp
// Author : Jean Anquetil
// Date : 30/12/2024
//------------------------------------------------------------------------------

#include "../../file_h/graphics/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//------------------------------------------------------------------------------

Texture::Texture(const std::string image_path)
{
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    // Configuration de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Configuration du filtrage de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    this->load_texture(image_path);
}

//------------------------------------------------------------------------------

void Texture::load_texture(const std::string image_path)
{
    // Charger l'image, créer une texture et générer des mipmaps
    int width, height, nrChannels;
    unsigned char* data = stbi_load(image_path.c_str(), &width, &height, &nrChannels, 0);
    
    if (data)
    {
        if (nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Échec du chargement de l'image " << image_path << std::endl;
    }
    stbi_image_free(data);
}

//------------------------------------------------------------------------------

void Texture::bind_texture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
}

//------------------------------------------------------------------------------

void Texture::unbind_texture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

//------------------------------------------------------------------------------

Texture::~Texture()
{
    glDeleteTextures(1, &_texture);
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------