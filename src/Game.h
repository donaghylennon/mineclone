#pragma once

#include "Player.h"
#include "Window.h"
#include "Renderer.h"
#include "World.h"

class Game {
private:
    Window *window;
    Renderer *renderer;
    World *world;
    Camera *camera;
    Player *player;
    float last_frame_time = 0.0f;
    float delta_time;
public:
    Game();
    ~Game();
    World *get_world();
    Player *get_player();
    Camera *get_camera();
    Renderer *get_renderer();
    void loop();
};
