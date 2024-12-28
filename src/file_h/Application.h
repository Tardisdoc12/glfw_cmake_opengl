//------------------------------------------------------------------------------
// Name of this file : Application.h
// Author : Jean Anquetil
// Date : 27/12/2024
//------------------------------------------------------------------------------
#pragma once
#include <GLFW/glfw3.h>

//------------------------------------------------------------------------------

class Application
{
public:
    Application();

    ~Application();

    void run();

private:
    GLFWwindow* _window;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------