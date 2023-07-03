#include "Camera.h"
#include <optional>
#include <unordered_set>
#include <vector>

Camera::Camera(glm::vec3 position) {
    this->position = position;
    this->world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->pitch = 0.0f;
    this->yaw = -90.0f;
    this->update();
}

void Camera::translate(glm::vec3 direction) {
    this->position += direction;
    this->update();
}

void Camera::rotate(float x, float y) {
    this->yaw += x;
    this->pitch += y;

    if (this->pitch > 89.0f)
        this->pitch = 89.0f;
    else if (this->pitch < -89.0f)
        this->pitch = -89.0f;

    if (this->yaw > 180)
        this->yaw -= 360;
    else if (this->yaw <= -180)
        this->yaw += 360;

    this->update();
}

void Camera::move(Direction d, float distance) {
    switch (d) {
    case FORWARD:
        this->position += distance * this->front;
        break;
    case BACKWARD:
        this->position -= distance * this->front;
        break;
    case LEFT:
        this->position -= distance * glm::normalize(glm::cross(this->front,
                    this->world_up));
        break;
    case RIGHT:
        this->position += distance * glm::normalize(glm::cross(this->front,
                    this->world_up));
        break;
    }
    this->update();
}

void Camera::update() {
    glm::vec3 direction = glm::vec3(
            cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
            sin(glm::radians(this->pitch)),
            sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)));
    this->front = glm::normalize(direction);
    this->view = glm::lookAt(this->position, this->position + this->front, this->world_up);
    this->moved_since_last_highlight_check = true;
}

glm::mat4 Camera::get_view() {
    return this->view;
}

std::optional<glm::vec3> Camera::get_faced_block_pos(World *world) {
    if (this->moved_since_last_highlight_check) {
        this->moved_since_last_highlight_check = false;
        std::unordered_set<glm::vec3>& blocks = world->get_blocks();
        bool found = false;
        for (float i = 0; i < 10; i++) {
            glm::vec3 coords = glm::floor(this->position + i*this->front + glm::vec3(0.5f));
            //glm::vec3 coords = glm::ceil(this->position + i*this->front);
            auto result = blocks.find(coords);
            if (result != blocks.end()) {
                this->last_faced_block_position = coords;
                found = true;
                break;
            }
        }
        if (!found)
            this->last_faced_block_position = {};
    }
    return this->last_faced_block_position;
}
