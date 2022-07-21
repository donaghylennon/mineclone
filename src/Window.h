#pragma once

#include "Renderer.h"

#include <GLFW/glfw3.h>

class Window {
private:
    int width;
    int height;
    float last_frame_time;
    float delta_time;
    GLFWwindow *window;
    Renderer *renderer;

public:
    Window(int width, int height);
    ~Window();
    //void set_dimensions(int width, int height);
    void loop();
};
