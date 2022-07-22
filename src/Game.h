#pragma once

#include "Window.h"
#include "Renderer.h"
#include "World.h"

class Game {
private:
    Window *window;
    Renderer *renderer;
    World *world;
    float last_frame_time;
    float delta_time;
public:
    Game();
    ~Game();
    void loop();
};
