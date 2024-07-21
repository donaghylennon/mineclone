#include "Player.h"
#include "Camera.h"

Player::Player(glm::vec3 position)
    : position(position), size(1.0f, 2.0f, 1.0f) {
}

void Player::move(float elapsed_time, World *world) {
    this->velocity.y += -150 * elapsed_time;
    glm::vec3 new_position = this->position + elapsed_time*this->velocity;

    auto blocks = world->get_blocks();
    //TODO: Calculate trajectory and check if any blocks would collide with the
    //player on that trajectory
    if (velocity.x >= 0) {
        for (int x_between = std::ceil(this->position.x);
                x_between <= std::floor(new_position.x + this->size.x/2);
                x_between++) {
            if (blocks.find({x_between,
                        std::floor(this->position.y),
                        std::floor(this->position.z)}) != blocks.end()) {
                new_position.x = x_between - this->size.x/2;
                velocity.x = 0;
                break;
            }
        }
    } else {
        for (int x_between = std::floor(this->position.x);
                x_between >= std::floor(new_position.x - this->size.x/2);
                x_between--) {
            if (blocks.find({x_between,
                        std::floor(this->position.y),
                        std::floor(this->position.z)}) != blocks.end()) {
                new_position.x = x_between + 1 + this->size.x/2;
                velocity.x = 0;
                break;
            }
        }
    }
    this->grounded = false;
    if (velocity.y >= 0) {
        for (float y_between = this->position.y + this->size.y;
                y_between <= std::ceil(new_position.y + this->size.y);
                y_between++) {
            if (blocks.find({std::floor(this->position.x),
                        std::floor(y_between),
                        std::floor(this->position.z)}) != blocks.end()) {
                new_position.y = std::floor(y_between) - this->size.y;
                velocity.y = 0;
            }
        }
    } else {
        for (float y_between = this->position.y;
                y_between >= std::floor(new_position.y);
                y_between--) {
            if (blocks.find({std::floor(this->position.x),
                        std::floor(y_between),
                        std::floor(this->position.z)}) != blocks.end()) {
                new_position.y = (std::floor(y_between) + 1);
                velocity.y = 0;
                this->grounded = true;
                break;
            }
        }
    }
    if (velocity.z >= 0) {
        for (int z_between = std::ceil(this->position.z);
                z_between <= std::floor(new_position.z + this->size.z/2);
                z_between++) {
            if (blocks.find({std::floor(this->position.x),
                        std::floor(this->position.y),
                        z_between}) != blocks.end()) {
                new_position.z = z_between - this->size.z/2;
                velocity.z = 0;
                break;
            }
        }
    } else {
        for (int z_between = std::floor(this->position.z);
                z_between >= std::floor(new_position.z - this->size.z/2);
                z_between--) {
            if (blocks.find({std::floor(this->position.x),
                        std::floor(this->position.y),
                        z_between}) != blocks.end()) {
                new_position.z = z_between + 1 + this->size.z/2;
                velocity.z = 0;
                break;
            }
        }
    }

    this->velocity *= 0.75;
    if (std::abs(this->velocity.x) < 0.5f)
        this->velocity.x = 0.0f;
    if (std::abs(this->velocity.y) < 0.5f)
        this->velocity.y = 0.0f;
    if (std::abs(this->velocity.z) < 0.5f)
        this->velocity.z = 0.0f;

    this->position = new_position;
}

void Player::set_movement_direction(Direction d, float speed) {
    float new_velocity_x = this->velocity.x;
    float new_velocity_y = this->velocity.y;
    float new_velocity_z = this->velocity.z;
    switch (d) {
    case FORWARD:
        new_velocity_x = speed * std::cos(glm::radians(this->yaw));
        new_velocity_z = speed * std::sin(glm::radians(this->yaw));
        break;
    case BACKWARD:
        new_velocity_x = -speed * std::cos(glm::radians(this->yaw));
        new_velocity_z = -speed * std::sin(glm::radians(this->yaw));
        break;
    case LEFT:
        new_velocity_x = -speed * std::cos(glm::radians(this->yaw+90.0f));
        new_velocity_z = -speed * std::sin(glm::radians(this->yaw+90.0f));
        break;
    case RIGHT:
        new_velocity_x = speed * std::cos(glm::radians(this->yaw+90.0f));
        new_velocity_z = speed * std::sin(glm::radians(this->yaw+90.0f));
        break;
    case UP:
        if (!this->grounded)
            break;
        new_velocity_y = speed;
        break;
    }
    this->velocity.x = new_velocity_x;
    this->velocity.y = new_velocity_y;
    this->velocity.z = new_velocity_z;
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
