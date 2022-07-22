#pragma once

#include "Renderer.h"

#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow *window;

public:
    Window(int width, int height);
    ~Window();
    //void set_dimensions(int width, int height);
    void set_callback_renderer(Renderer *renderer);
    bool should_close();
    float get_time();
    void swap_buffers();
    void poll_events();
};
