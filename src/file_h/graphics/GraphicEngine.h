//------------------------------------------------------------------------------
// Name of this file : GraphicEngine.h
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#pragma once
#include <iostream>
#include <map>
#include "Framebuffer.h"

//------------------------------------------------------------------------------

class GraphicEngine
{
public:
    GraphicEngine();

    ~GraphicEngine();

    void update();

    void render(GLFWwindow* window);

private:
    std::map<int, Framebuffer> _framebuffers;
    //std::vector<Shader> _shaders;
    //std::vector<Texture> _textures;

};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------