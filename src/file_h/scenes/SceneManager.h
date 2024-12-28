//------------------------------------------------------------------------------
// Name of this file : SceneManager.h
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#pragma once
#include <vector>
#include "Scene.h"

//------------------------------------------------------------------------------

class SceneManager
{
public:
    SceneManager();

    SceneManager(Scene& sceneInitial);

    ~SceneManager();

    bool isEmpty();

    void input();

    void update();

    void render();

    void addScene(Scene& scene);

    void removeScene(Scene& scene);

    void setScene(Scene& scene);

private:
    std::vector<Scene> _scenes;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------