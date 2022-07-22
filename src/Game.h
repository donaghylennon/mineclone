#pragma once

#include "Window.h"
#include "Renderer.h"
#include "World.h"

class Game {
private:
    Window *window;
    Renderer *renderer;
    World *world;
    Camera *camera;
    float last_frame_time;
    float delta_time;
public:
    Game();
    ~Game();
    Camera *get_camera();
    Renderer *get_renderer();
    void loop();
};
