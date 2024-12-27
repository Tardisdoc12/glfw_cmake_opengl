//------------------------------------------------------------------------------
// Name of this file : Framebuffer.h
// Author : Jean Anquetil
// Date : 27/12/2024
//------------------------------------------------------------------------------

#pragma once
#include <GLFW/glfw3.h>

class Framebuffer
{
public:
    Framebuffer();
    ~Framebuffer();

    void bind();
    void unbind();

    void clear();

    void resize(int width, int height);

    GLuint getTexture() const;
private:
    GLuint m_fbo;
    GLuint m_texture;
    GLuint m_depthBuffer;
    int m_width;
    int m_height;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------