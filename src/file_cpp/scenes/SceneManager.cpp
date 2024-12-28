//------------------------------------------------------------------------------
// Name of this file : SceneManager.cpp
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#include "../file_h/scenes/SceneManager.h"

//------------------------------------------------------------------------------

SceneManager::SceneManager()
{
}

//------------------------------------------------------------------------------

SceneManager::SceneManager(Scene& sceneInitial)
{
    this->addScene(sceneInitial);
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
        _scenes.back().input();
    }
}

//------------------------------------------------------------------------------

void SceneManager::update()
{
    if (!isEmpty())
    {
        _scenes.back().update();
    }
}

//------------------------------------------------------------------------------

void SceneManager::render()
{
    if (!isEmpty())
    {
        _scenes.back().render();
    }
}

//------------------------------------------------------------------------------

void SceneManager::addScene(Scene& scene)
{
    if(!isEmpty())
    {
        _scenes.back().on_Exit();
    }
    _scenes.push_back(scene);
    _scenes.back().on_Enter();
}

//------------------------------------------------------------------------------

void SceneManager::removeScene(Scene& scene)
{
    if (!isEmpty())
    {
        _scenes.back().on_Exit();
        _scenes.pop_back();
    }
}

//------------------------------------------------------------------------------

void SceneManager::setScene(Scene& scene)
{
    if (!isEmpty())
    {
        _scenes.back().on_Exit();
        _scenes.pop_back();
    }
    _scenes.push_back(scene);
    _scenes.back().on_Enter();
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------