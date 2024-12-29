//------------------------------------------------------------------------------
// Name of this file : GraphicEngine.cpp
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#include "../../file_h/graphics/GraphicEngine.h"

//------------------------------------------------------------------------------

GraphicEngine::GraphicEngine()
{
}

//------------------------------------------------------------------------------

GraphicEngine::~GraphicEngine(){
    if (_framebuffers.empty()){
        return;
    }
    for(auto& framebuffer : _framebuffers){
        framebuffer.second.~Framebuffer();
    }
}

//------------------------------------------------------------------------------

void GraphicEngine::update()
{
    std::cout << "GraphicEngine update\n"<< std::endl;
}

//------------------------------------------------------------------------------

void GraphicEngine::render()
{
    std::cout << "GraphicEngine render\n"<< std::endl;
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------