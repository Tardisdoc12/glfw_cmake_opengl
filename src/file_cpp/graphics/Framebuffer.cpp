//------------------------------------------------------------------------------
// Name of this file : Framebuffer.cpp
// Author : Jean Anquetil
// Date : 27/12/2024
//------------------------------------------------------------------------------
#include "../../file_h/graphics/Framebuffer.h"

//------------------------------------------------------------------------------
// ColorBuffer

ColorBuffer::ColorBuffer(int width, int height, GLenum internalFormat, GLenum format, GLenum type)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//------------------------------------------------------------------------------

ColorBuffer::~ColorBuffer()
{
    glDeleteTextures(1, &textureID);
}

//------------------------------------------------------------------------------

GLuint ColorBuffer::getTexture() const
{
    return textureID;
}

//------------------------------------------------------------------------------
// DepthStencilBuffer

DepthStencilBuffer::DepthStencilBuffer(int width, int height, GLenum format, GLenum attachment)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//------------------------------------------------------------------------------

DepthStencilBuffer::~DepthStencilBuffer()
{
    glDeleteTextures(1, &textureID);
}

//------------------------------------------------------------------------------

GLuint DepthStencilBuffer::getTexture() const
{
    return textureID;
}

//------------------------------------------------------------------------------
// Framebuffer

Framebuffer::Framebuffer()
{
    glGenFramebuffers(1, &framebufferID);
}

//------------------------------------------------------------------------------

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &framebufferID);
}

//------------------------------------------------------------------------------

void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
}

//------------------------------------------------------------------------------

void Framebuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//------------------------------------------------------------------------------

void Framebuffer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

//------------------------------------------------------------------------------

GLuint Framebuffer::getTexture() const
{
    return 0;
}

//------------------------------------------------------------------------------

void Framebuffer::attachTexture(GLuint textureID, GLenum attachmentType) {
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, textureID, 0);
    attachments.push_back(textureID);
    unbind();
}

//------------------------------------------------------------------------------

void Framebuffer::attachRenderbuffer(GLuint renderbufferID, GLenum attachmentType) {
    bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentType, GL_RENDERBUFFER, renderbufferID);
    unbind();
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------