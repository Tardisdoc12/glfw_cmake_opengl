#include <GLFW/glfw3.h>

#pragma once

class Application
{
public:
    Application();

    ~Application();

    void run();

private:
    GLFWwindow* window;
};