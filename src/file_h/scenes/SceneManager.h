//------------------------------------------------------------------------------
// Name of this file : SceneManager.h
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#pragma once
#include <vector>
#include <memory>
#include "Scene.h"

//------------------------------------------------------------------------------

class SceneManager
{
public:
    SceneManager();

    SceneManager(std::unique_ptr<Scene> sceneInitial);

    ~SceneManager();

    bool isEmpty();

    void input();

    void update();

    void render();

    void addScene(std::unique_ptr<Scene> scene);

    void removeScene(std::unique_ptr<Scene> scene);

    void setScene(std::unique_ptr<Scene> scene);

private:
    std::vector<std::unique_ptr<Scene>> _scenes;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------