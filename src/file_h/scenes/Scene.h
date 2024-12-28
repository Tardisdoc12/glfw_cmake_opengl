//------------------------------------------------------------------------------
// Name of this file : Scene.h
// Author : Jean Anquetil
// Date : 28/12/2024
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

class Scene
{
public:
    Scene();

    ~Scene();

    virtual void input();

    virtual void update();

    virtual void render();

    virtual void on_Enter();

    virtual void on_Exit();
private:
    // GraphicEngine _graphicEngine;
    // PhysicsEngine _physicsEngine;
    // AudioEngine _audioEngine;
    // InputEngine _inputEngine;
};

//------------------------------------------------------------------------------
// END OF FILE
//------------------------------------------------------------------------------