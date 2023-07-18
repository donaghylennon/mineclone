#pragma once

#include "Camera.h"

#include <glm/glm.hpp>

class Player {
    friend class Camera;
private:
    glm::vec3 position;
    glm::vec3 size;
    float pitch = 0.0f;
    float yaw = -90.0f;
public:
    Player(glm::vec3 position);
    void move(Direction d, float distance);
    void rotate(float x, float y);
};
