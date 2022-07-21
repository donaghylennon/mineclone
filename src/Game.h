#pragma once

#include "Window.h"
#include "World.h"

class Game {
private:
    Window *window;
    //Renderer *renderer;
    World *world;
public:
    Game();
    ~Game();
    void loop();
};
