#include "Window.h"

#include <iostream>

Window::Window(int width, int height) {
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
}

Window::~Window() {
    glfwTerminate();
}

void Window::set_callback_renderer(Renderer *renderer) {
    glfwSetWindowUserPointer(this->window, (void*)renderer);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int w, int h) {
            Renderer *renderer = (Renderer*)glfwGetWindowUserPointer(window);
            renderer->set_viewport(w, h);
        });
}

bool Window::should_close() {
    return glfwWindowShouldClose(this->window);
}

float Window::get_time() {
    return glfwGetTime();
}

void Window::swap_buffers() {
    glfwSwapBuffers(this->window);
}

void Window::poll_events() {
    glfwPollEvents();
}
