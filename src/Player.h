#pragma once

#include "Camera.h"
#include "World.h"

#include <glm/glm.hpp>

enum Direction {
    LEFT, RIGHT, FORWARD, BACKWARD, UP
};

class Player {
    friend class Camera;
private:
    glm::vec3 position;
    glm::vec3 velocity{0};
    glm::vec3 size;
    float pitch = 0.0f;
    float yaw = -90.0f;
    bool grounded = false;
public:
    Player(glm::vec3 position);
    void move(float elapsed_time, World *world);
    void set_movement_direction(Direction d, float speed);
    void rotate(float x, float y);
};
