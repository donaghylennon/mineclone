#pragma once

#include "World.h"

#include <optional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Direction {
    LEFT, RIGHT, FORWARD, BACKWARD
};

enum BlockFace {
    NORTH, EAST, SOUTH, WEST, TOP, BOTTOM
};

class Camera {
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 world_up;
    float pitch;
    float yaw;
    glm::mat4 view;

    bool moved_since_last_highlight_check;
    std::optional<glm::vec3> last_faced_block_position;
    BlockFace last_faced_block_face = NORTH;
public:
    Camera(glm::vec3 position);
    void translate(glm::vec3 direction);
    void move(Direction d, float distance);
    void rotate(float x, float y);
    void update();
    glm::mat4 get_view();

    std::optional<glm::vec3> get_faced_block_pos(World *world);
    BlockFace get_last_faced_block_face();
};
