//------------------------------------------------------------------------------
// Name of this file : StartingScene.cpp
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#include "../../file_h/scenes/StartingScene.h"
#include "../../file_h/globals/variables.h"
#include <iostream>


//------------------------------------------------------------------------------

StartingScene::StartingScene()
{
    globals::entitiesCor["cat"] = 0;
    globals::entitiesCor["screen"] = 1;
    _graphicEngine = GraphicEngine();
}

//------------------------------------------------------------------------------

StartingScene::~StartingScene() = default;

//------------------------------------------------------------------------------

void StartingScene::input()
{
    //to do
}

//------------------------------------------------------------------------------

void StartingScene::update(SceneManager* sceneManager, float dt)
{
    _graphicEngine.update();
}

//------------------------------------------------------------------------------

void StartingScene::render(GLFWwindow* window)
{
    _graphicEngine.render(window);
}

//------------------------------------------------------------------------------

void StartingScene::on_Enter()
{
    // to do
}

//------------------------------------------------------------------------------

void StartingScene::on_Exit()
{
    //to do
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------
