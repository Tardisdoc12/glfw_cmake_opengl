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

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureID, 0);

    glGenRenderbuffers(1, &_renderbufferID);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderbufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderbufferID);

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
    return _textureID;
}

//------------------------------------------------------------------------------

void Framebuffer::attachTexture(GLuint textureID, GLenum attachmentType) {
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, textureID, 0);
    attachments.push_back(textureID);
    _textureID = textureID;
    unbind();
}

//------------------------------------------------------------------------------

void Framebuffer::attachRenderbuffer(GLuint renderbufferID, GLenum attachmentType) {
    bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentType, GL_RENDERBUFFER, renderbufferID);
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