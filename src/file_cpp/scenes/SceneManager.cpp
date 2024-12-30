//------------------------------------------------------------------------------
// Name of this file : SceneManager.cpp
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#include <memory>
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../file_h/scenes/SceneManager.h"

//------------------------------------------------------------------------------

SceneManager::SceneManager()
{
}

//------------------------------------------------------------------------------

SceneManager::SceneManager(std::unique_ptr<Scene> sceneInitial)
{
    this->addScene(std::move(sceneInitial));
}

//------------------------------------------------------------------------------

SceneManager::~SceneManager() = default;

//------------------------------------------------------------------------------

bool SceneManager::isEmpty()
{
    return _scenes.empty();
}

//------------------------------------------------------------------------------

void SceneManager::input()
{
    if (!isEmpty())
    {
        _scenes.back()->input();
    }
}

//------------------------------------------------------------------------------

void SceneManager::update(float fps)
{
    if (!isEmpty())
    {
        _scenes.back()->update(this, fps);
    }
}

//------------------------------------------------------------------------------

void SceneManager::render(GLFWwindow* window)
{
    if (!isEmpty())
    {
        _scenes.back()->render(window);
    }
}

//------------------------------------------------------------------------------

void SceneManager::addScene(std::unique_ptr<Scene> scene)
{
    if(!isEmpty())
    {
        _scenes.back()->on_Exit();
    }
    _scenes.push_back(std::move(scene));
    _scenes.back()->on_Enter();
}

//------------------------------------------------------------------------------

void SceneManager::removeScene(std::unique_ptr<Scene> scene)
{
    if (!isEmpty())
    {
        _scenes.back()->on_Exit();
        _scenes.pop_back();
    }
}

//------------------------------------------------------------------------------

void SceneManager::setScene(std::unique_ptr<Scene> scene)
{
    if (!isEmpty())
    {
        _scenes.back()->on_Exit();
        _scenes.pop_back();
    }
    _scenes.push_back(std::move(scene));
    _scenes.back()->on_Enter();
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------