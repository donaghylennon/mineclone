#include "Window.h"

#include <iostream>

Window::Window(int width, int height) {
    this->width = width;
    this->height = height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(width, height, "Minecraft", NULL, NULL);
    if (this->window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(this->window);
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(this->window, (void*)this);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int w, int h) {
            Window *win = (Window*)glfwGetWindowUserPointer(window);
            win->renderer->set_viewport(w, h);
        });

    this->renderer = new Renderer(width, height);
}

Window::~Window() {
    delete this->renderer;
    glfwTerminate();
}

void Window::loop() {
    while (!glfwWindowShouldClose(this->window)) {
        float current_frame_time = glfwGetTime();
        this->delta_time = current_frame_time - this->last_frame_time;
        this->last_frame_time = current_frame_time;

        glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
