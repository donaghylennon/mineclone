#pragma once

#include <unordered_set>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

using position = glm::ivec3;

class World {
private:
    //std::unordered_map<position, Block> map;
    std::unordered_set<position> map;
public:
    World();
    std::unordered_set<position>& get_blocks();
    void place_block(glm::ivec3 pos);
};
