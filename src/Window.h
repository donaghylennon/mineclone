#pragma once

#include "Player.h"
#include "Renderer.h"
#include "Camera.h"

#include <GLFW/glfw3.h>

class Game;

class Window {
private:
    GLFWwindow *window;
    float last_block_place_time = 0.0f; // move this (and block placement) somewhere better

public:
    Window(int width, int height);
    ~Window();
    void set_user_pointer(Game *game);
    bool should_close();
    float get_time();
    void swap_buffers();
    void poll_events();
    void process_input(Game *game);
};
