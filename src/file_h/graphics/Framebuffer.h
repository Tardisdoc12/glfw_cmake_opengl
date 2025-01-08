//------------------------------------------------------------------------------
// Name of this file : Framebuffer.h
// Author : Jean Anquetil
// Date : 27/12/2024
//------------------------------------------------------------------------------

#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//------------------------------------------------------------------------------

class ColorBuffer
{
private:
    GLuint textureID;
public:
    ColorBuffer(int width, int height, GLenum internalFormat = GL_RGB, GLenum format = GL_RGB, GLenum type = GL_UNSIGNED_BYTE);
    ~ColorBuffer();

    GLuint getTexture() const;
};

//------------------------------------------------------------------------------

class DepthStencilBuffer
{
private:
    GLuint textureID;

public:
    DepthStencilBuffer(int width, int height, GLenum format = GL_DEPTH24_STENCIL8, GLenum attachment = GL_DEPTH_STENCIL_ATTACHMENT);
    ~DepthStencilBuffer();

    GLuint getTexture() const;
};

//------------------------------------------------------------------------------

class Framebuffer
{
public:
    Framebuffer();
    ~Framebuffer();

    Framebuffer(int width, int height);

    void bind();
    void unbind();

    void clear();
    void attachTexture(GLuint textureID, GLenum attachmentType = GL_COLOR_ATTACHMENT0);
    void attachRenderbuffer(GLuint renderbufferID, GLenum attachmentType = GL_DEPTH_STENCIL_ATTACHMENT);

    GLuint getTexture() const;

    bool isComplete();
private:
    GLuint framebufferID;
    std::vector<GLuint> attachments;
    GLuint _renderbufferID;
    GLuint _textureID;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------