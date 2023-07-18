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

class Player;

class Camera {
private:
    Player& player;
    glm::vec3 front;
    glm::vec3 world_up;
    glm::mat4 view;

    bool moved_since_last_highlight_check;
    std::optional<glm::ivec3> last_faced_block_position;
    BlockFace last_faced_block_face = NORTH;
public:
    Camera(Player& player);
    glm::vec3 position();
    void update();
    glm::mat4 get_view();

    std::optional<glm::ivec3> get_faced_block_pos(World *world);
    BlockFace get_last_faced_block_face();
};
