#include "Camera.h"
#include "Player.h"

#include <cmath>
#include <unordered_set>
#include <vector>

Camera::Camera(Player& player) : player(player) {
    this->world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->update();
}

glm::vec3 Camera::position() {
    return player.position + glm::vec3(0.0f, 2.0f, 0.0f);
}

void Camera::update() {
    glm::vec3 direction = glm::vec3(
            cos(glm::radians(player.yaw)) * cos(glm::radians(player.pitch)),
            sin(glm::radians(player.pitch)),
            sin(glm::radians(player.yaw)) * cos(glm::radians(player.pitch)));
    this->front = glm::normalize(direction);
    this->view = glm::lookAt(this->position(), this->position() + this->front, this->world_up);
    this->moved_since_last_highlight_check = true;
}

glm::mat4 Camera::get_view() {
    return this->view;
}

std::optional<glm::ivec3> Camera::get_faced_block_pos(World *world) {
    if (this->moved_since_last_highlight_check) {
        this->moved_since_last_highlight_check = false;
        auto& blocks = world->get_blocks();
        bool found = false;

        glm::vec3 start = this->position();
        glm::vec3 ray_direction = this->front;

        glm::vec3 ray_unit_step_size = {
            std::sqrt(1 + (ray_direction.y/ray_direction.x)
                    * (ray_direction.y/ray_direction.x)
                    + (ray_direction.z/ray_direction.x)
                    * (ray_direction.z/ray_direction.x)),
            std::sqrt(1 + (ray_direction.x/ray_direction.y)
                    * (ray_direction.x/ray_direction.y)
                    + (ray_direction.z/ray_direction.y)
                    * (ray_direction.z/ray_direction.y)),
            std::sqrt(1 + (ray_direction.x/ray_direction.z)
                    * (ray_direction.x/ray_direction.z)
                    + (ray_direction.y/ray_direction.z)
                    * (ray_direction.y/ray_direction.z)),
        };

        glm::ivec3 current_pos = glm::floor(start);

        glm::vec3 ray_length_1D;
        glm::ivec3 step;

        if (ray_direction.x < 0) {
            step.x = -1;
            ray_length_1D.x = (start.x - (float)current_pos.x)
                * ray_unit_step_size.x;
        } else {
            step.x = 1;
            ray_length_1D.x = ((float)(current_pos.x + 1) - start.x)
                * ray_unit_step_size.x;
        }
        if (ray_direction.y < 0) {
            step.y = -1;
            ray_length_1D.y = (start.y - (float)current_pos.y)
                * ray_unit_step_size.y;
        } else {
            step.y = 1;
            ray_length_1D.y = ((float)(current_pos.y + 1) - start.y)
                * ray_unit_step_size.y;
        }
        if (ray_direction.z < 0) {
            step.z = -1;
            ray_length_1D.z = (start.z - (float)current_pos.z)
                * ray_unit_step_size.z;
        } else {
            step.z = 1;
            ray_length_1D.z = ((float)(current_pos.z + 1) - start.z)
                * ray_unit_step_size.z;
        }

        float max_distance = 10.0f;
        float distance = 0.0f;
        glm::ivec3 prev_pos = current_pos;

        while (!found && std::abs(distance) < max_distance) {
            prev_pos = current_pos;
            if (ray_length_1D.x < ray_length_1D.y
                    && ray_length_1D.x < ray_length_1D.z) {
                current_pos.x += step.x;
                ray_length_1D.x += ray_unit_step_size.x;
                distance = ray_length_1D.x;
            } else if (ray_length_1D.y < ray_length_1D.x
                    && ray_length_1D.y < ray_length_1D.z) {
                current_pos.y += step.y;
                ray_length_1D.y += ray_unit_step_size.y;
                distance = ray_length_1D.y;
            } else {
                current_pos.z += step.z;
                ray_length_1D.z += ray_unit_step_size.z;
                distance = ray_length_1D.z;
            }

            if (blocks.find(current_pos) != blocks.end()) {
                found = true;
                this->last_faced_block_position = current_pos;
                glm::ivec3 diff = current_pos - prev_pos;
                if (diff.x) {
                    this->last_faced_block_face = diff.x >= 0 ? WEST : EAST;
                } else if (diff.y) {
                    this->last_faced_block_face = diff.y >= 0 ? BOTTOM : TOP;
                } else if (diff.z) {
                    this->last_faced_block_face = diff.z >= 0 ? SOUTH : NORTH;
                }
            }
        }

        if (!found)
            this->last_faced_block_position = {};
    }
    return this->last_faced_block_position;
}

BlockFace Camera::get_last_faced_block_face() {
    return this->last_faced_block_face;
}
