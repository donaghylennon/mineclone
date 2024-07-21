#include "Window.h"

#include "Camera.h"
#include "Game.h"
#include "Player.h"

#include <GLFW/glfw3.h>
#include <iostream>

Window::Window(int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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

    game->get_player()->rotate(xoffset, yoffset);
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

void Window::process_input(Game *game) {
    World *world = game->get_world();
    Player *player = game->get_player();
    Camera *camera = game->get_camera();
    const float player_speed = 7.0f;
    if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, GLFW_TRUE);
    //TODO: Make walk, jump, run methods on player instead
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
        player->set_movement_direction(FORWARD, player_speed);
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
        player->set_movement_direction(BACKWARD, player_speed);
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
        player->set_movement_direction(LEFT, player_speed);
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
        player->set_movement_direction(RIGHT, player_speed);
    if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
        player->set_movement_direction(UP, 45.0f);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        float current_time = this->get_time();
        if (current_time - this->last_block_place_time > 0.2f) {
            this->last_block_place_time = current_time;
            if (auto faced_block = camera->get_faced_block_pos(world)) {
                BlockFace face = camera->get_last_faced_block_face();
                glm::ivec3 change;
                switch (face) {
                    case NORTH:
                        change = glm::ivec3(0.0, 0.0, 1.0);
                        break;
                    case EAST:
                        change = glm::ivec3(1.0, 0.0, 0.0);
                        break;
                    case SOUTH:
                        change = glm::ivec3(0.0, 0.0, -1.0);
                        break;
                    case WEST:
                        change = glm::ivec3(-1.0, 0.0, 0.0);
                        break;
                    case TOP:
                        change = glm::ivec3(0.0, 1.0, 0.0);
                        break;
                    case BOTTOM:
                        change = glm::ivec3(0.0, -1.0, 0.0);
                        break;
                    default:
                        return;
                }
                world->place_block(faced_block.value() + change, 1);
            }
        }
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        float current_time = this->get_time();
        if (current_time - this->last_block_place_time > 0.2f) {
            this->last_block_place_time = current_time;
            if (auto faced_block = camera->get_faced_block_pos(world)) {
                BlockFace face = camera->get_last_faced_block_face();
                world->remove_block(faced_block.value());
            }
        }
    }
}
