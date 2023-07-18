#include "Player.h"
#include "Camera.h"

Player::Player(glm::vec3 position)
    : position(position), size(1.0f, 2.0f, 1.0f) {
}

void Player::move(Direction d, float distance) {
    switch (d) {
    case FORWARD:
        this->position += glm::vec3(distance * std::cos(glm::radians(this->yaw)), 0.0f,
                distance * std::sin(glm::radians(this->yaw)));
        break;
    case BACKWARD:
        this->position -= glm::vec3(distance * std::cos(glm::radians(this->yaw)), 0.0f,
                distance * std::sin(glm::radians(this->yaw)));
        break;
    case LEFT:
        this->position -= glm::vec3(distance * std::cos(glm::radians(this->yaw+90.0f)),
                0.0f, distance * std::sin(glm::radians(this->yaw+90.0f)));
        break;
    case RIGHT:
        this->position += glm::vec3(distance * std::cos(glm::radians(this->yaw+90.0f)),
                0.0f, distance * std::sin(glm::radians(this->yaw+90.0f)));
        break;
    }
}

void Player::rotate(float x, float y) {
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
}
