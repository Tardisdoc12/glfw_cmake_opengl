//------------------------------------------------------------------------------
// Name of this file : StartingScene.cpp
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#include "../../file_h/scenes/StartingScene.h"
#include <iostream>


//------------------------------------------------------------------------------

StartingScene::StartingScene()
{
    std::cout << "StartingScene constructor "<< std::endl;
}

//------------------------------------------------------------------------------

StartingScene::~StartingScene()
{
    std::cout << "StartingScene destructor "<< std::endl;
}

//------------------------------------------------------------------------------

void StartingScene::input()
{
    std::cout << "StartingScene input "<< std::endl;
}

//------------------------------------------------------------------------------

void StartingScene::update(SceneManager* sceneManager)
{
    std::cout << "StartingScene update "<< std::endl;
    _graphicEngine.update();
}

//------------------------------------------------------------------------------

void StartingScene::render(GLFWwindow* window)
{
    std::cout << "StartingScene render "<< std::endl;
    _graphicEngine.render(window);
}

//------------------------------------------------------------------------------

void StartingScene::on_Enter()
{
    std::cout << "StartingScene on_Enter "<< std::endl;
}

//------------------------------------------------------------------------------

void StartingScene::on_Exit()
{
    std::cout << "StartingScene on_Exit "<< std::endl;
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------