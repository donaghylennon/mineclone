#include "Window.h"

#include "Game.h"

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


float prev_x = 0.0f;
float prev_y = 0.0f;
bool first_mouse = true;

void cursor_callback(GLFWwindow *window, double xpos, double ypos) {
    if (first_mouse) {
        prev_x = xpos;
        prev_y = ypos;
        first_mouse = false;
    }
    Game *game = (Game*)glfwGetWindowUserPointer(window);
    float xoffset = xpos - prev_x;
    float yoffset = prev_y - ypos;
    prev_x = xpos;
    prev_y = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    game->get_camera()->rotate(xoffset, yoffset);
}

void Window::set_user_pointer(Game *game) {
    glfwSetWindowUserPointer(this->window, (void*)game);
    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow *window, int w, int h) {
                Game *game = (Game*)glfwGetWindowUserPointer(window);
                game->get_renderer()->set_viewport(w, h);
            });
    glfwSetCursorPosCallback(this->window, cursor_callback);
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

void Window::process_input(Camera *camera) {
    const float camera_speed = 0.05f;
    if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, GLFW_TRUE);
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
        camera->move(FORWARD, camera_speed);
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
        camera->move(BACKWARD, camera_speed);
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
        camera->move(LEFT, camera_speed);
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
        camera->move(RIGHT, camera_speed);
}
