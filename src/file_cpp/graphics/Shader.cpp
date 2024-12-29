//------------------------------------------------------------------------------
// Name of this file : Shader.cpp
// Author : Jean Anquetil
// Date : 29/12/2024
//------------------------------------------------------------------------------

#include <fstream>
#include <sstream>
#include <iostream>

#include "../../file_h/graphics/Shader.h"

//------------------------------------------------------------------------------

std::string loadShaderSource(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

//------------------------------------------------------------------------------

unsigned int compileShader(const std::string& source, GLenum shaderType) {
    unsigned int shader = glCreateShader(shaderType);
    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    // Vérifier la compilation
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader Compilation Error (" << shaderType << "): " << infoLog << std::endl;
    }

    return shader;
}

//------------------------------------------------------------------------------

unsigned int linkShaderProgram(unsigned int vertexShader, unsigned int fragmentShader) {
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Vérifier la liaison
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Program Linking Error: " << infoLog << std::endl;
    }

    // Supprimer les shaders une fois liés
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

//------------------------------------------------------------------------------

Shader::Shader(const std::string vertexPath, const std::string fragmentPath)
{
    // Charger les sources des shaders
    std::string vertexSource = loadShaderSource(vertexPath);
    std::string fragmentSource = loadShaderSource(fragmentPath);

    // Compiler les shaders
    unsigned int vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    // Lier le programme
    unsigned int shaderProgram = linkShaderProgram(vertexShader, fragmentShader);

    // Stocker le shader program ID dans une variable membre
    _shaderProgram = shaderProgram;
    std::cout << "Shader program created with ID: " << _shaderProgram << std::endl;
}

//------------------------------------------------------------------------------

Shader::~Shader()
{
    if (_shaderProgram != 0) {
        glDeleteProgram(_shaderProgram);
    }
}

//------------------------------------------------------------------------------

void Shader::set_single_form(std::string uniform_type, std::string uniform_name)
{
    if(_single_uniform.find(uniform_type) != _single_uniform.end())
    {
        std::cerr << "Uniform type already exists" << std::endl;
        return;
    }
    _single_uniform[uniform_type] = uniform_name;
}

//------------------------------------------------------------------------------

void Shader::set_multi_form(std::string uniform_type, std::string uniform_name)
{
    if(_multi_uniform.find(uniform_type) == _multi_uniform.end())
    {
        _multi_uniform[uniform_type] = std::vector<std::string>();
    }
    _multi_uniform[uniform_type].push_back(uniform_name);
}

//------------------------------------------------------------------------------

std::string Shader::fetch_single_uniform(std::string uniform_name)
{
    if(_single_uniform.find(uniform_name) == _single_uniform.end())
    {
        std::cerr << "Uniform name not found" << std::endl;
        return "";
    }
    return _single_uniform[uniform_name];
}

//------------------------------------------------------------------------------

std::string Shader::fetch_multi_uniform(std::string uniform_name, int index)
{
    if(_multi_uniform.find(uniform_name) == _multi_uniform.end())
    {
        std::cerr << "Uniform name not found" << std::endl;
        return "";
    }
    if(index >= _multi_uniform[uniform_name].size())
    {
        std::cerr << "Index out of range" << std::endl;
        return "";
    }
    return _multi_uniform[uniform_name][index];
}

//------------------------------------------------------------------------------

void Shader::use()
{
    glUseProgram(_shaderProgram);
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------