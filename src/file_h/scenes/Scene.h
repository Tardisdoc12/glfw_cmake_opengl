//------------------------------------------------------------------------------
// Name of this file : Scene.h
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

class SceneManager;

//------------------------------------------------------------------------------

class Scene
{
public:

    virtual ~Scene() = default;

    virtual void input() = 0;

    virtual void update(SceneManager* sceneManager) = 0;

    virtual void render() = 0;

    virtual void on_Enter() = 0;

    virtual void on_Exit() = 0;
private:
    // GraphicEngine _graphicEngine;
    // PhysicsEngine _physicsEngine;
    // AudioEngine _audioEngine;
    // InputEngine _inputEngine;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------