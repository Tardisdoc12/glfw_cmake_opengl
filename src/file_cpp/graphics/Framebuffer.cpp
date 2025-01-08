//------------------------------------------------------------------------------
// Name of this file : Framebuffer.cpp
// Author : Jean Anquetil
// Date : 27/12/2024
//------------------------------------------------------------------------------

#include <iostream>

#include "../../file_h/graphics/Framebuffer.h"

//------------------------------------------------------------------------------
// ColorBuffer

ColorBuffer::ColorBuffer(int width, int height, GLenum internalFormat, GLenum format, GLenum type)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
    glGenRenderbuffers(1, &textureID);
    glBindRenderbuffer(GL_RENDERBUFFER, textureID);
    glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
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

Framebuffer::Framebuffer(int width, int height)
{
    glGenFramebuffers(1, &framebufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
    this->attachTexture(width, height);
    this->attachRenderbuffer(width, height);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Framebuffer is not complete" << std::endl;
    }
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
    return _colorBuffer->getTexture();
}

//------------------------------------------------------------------------------

void Framebuffer::attachTexture(int width, int height, GLenum attachmentType)
{
    _colorBuffer = std::make_shared<ColorBuffer>(width, height);
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, _colorBuffer->getTexture(), 0);
    unbind();
}

//------------------------------------------------------------------------------

void Framebuffer::attachRenderbuffer(int width, int height, GLenum attachmentType)
{
    _depthStencilBuffer = std::make_shared<DepthStencilBuffer>(width, height);
    bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentType, GL_RENDERBUFFER, _depthStencilBuffer->getTexture());
    unbind();
}

//------------------------------------------------------------------------------

bool Framebuffer::isComplete()
{
    this->bind();
    bool complete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    this->unbind();
    return complete;
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------