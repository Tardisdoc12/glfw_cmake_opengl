//------------------------------------------------------------------------------
// Name of this file : StartingScene.h
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#pragma once
#include "Scene.h"
#include "../graphics/GraphicEngine.h"

//------------------------------------------------------------------------------

class StartingScene: public Scene
{
public:
    StartingScene();

    ~StartingScene() override;

    void input() final;

    void update(SceneManager* sceneManager) final;

    void render(GLFWwindow* window) final;

    void on_Enter() final;

    void on_Exit() final;

private:
    GraphicEngine _graphicEngine;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------