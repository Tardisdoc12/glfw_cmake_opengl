//------------------------------------------------------------------------------
// Name of this file : Shader.h
// Author : Jean Anquetil
// Date : 29/12/2024
//------------------------------------------------------------------------------

#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//------------------------------------------------------------------------------

class Shader
{
public:
    Shader(const std::string vertexPath, const std::string fragmentPath);
    ~Shader();

    void set_single_form(std::string uniform_type, std::string uniform_name);
    void set_multi_form(std::string uniform_type, std::string uniform_name);

    std::string fetch_single_uniform(std::string uniform_name);
    std::string fetch_multi_uniform(std::string uniform_name, int index);

    void use();

private:
    std::map<std::string, std::string> _single_uniform;
    std::map<std::string, std::vector<std::string>> _multi_uniform;
    unsigned int _shaderProgram;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------