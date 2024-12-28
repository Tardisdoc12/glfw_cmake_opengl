//------------------------------------------------------------------------------
// Name of this file : StartingScene.h
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#pragma once
#include "Scene.h"

//------------------------------------------------------------------------------

class StartingScene: public Scene
{
public:
    StartingScene();

    ~StartingScene() override;

    void input() final;

    void update(SceneManager* sceneManager) final;

    void render() final;

    void on_Enter() final;

    void on_Exit() final;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------