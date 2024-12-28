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
    std::cout << "StartingScene constructor\n"<< std::endl;
}

//------------------------------------------------------------------------------

StartingScene::~StartingScene()
{
    std::cout << "StartingScene destructor\n"<< std::endl;
}

//------------------------------------------------------------------------------

void StartingScene::input()
{
    std::cout << "StartingScene input\n"<< std::endl;
}

//------------------------------------------------------------------------------

void StartingScene::update(SceneManager* sceneManager)
{
    std::cout << "StartingScene update\n"<< std::endl;
}

//------------------------------------------------------------------------------

void StartingScene::render()
{
    std::cout << "StartingScene render\n"<< std::endl;
}

//------------------------------------------------------------------------------

void StartingScene::on_Enter()
{
    std::cout << "StartingScene on_Enter\n"<< std::endl;
}

//------------------------------------------------------------------------------

void StartingScene::on_Exit()
{
    std::cout << "StartingScene on_Exit\n"<< std::endl;
}

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------