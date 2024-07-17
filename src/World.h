#pragma once

#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

using position = glm::ivec3;

class World {
private:
    //std::unordered_map<position, Block> map;
    std::unordered_map<position, int> map;
public:
    World();
    std::unordered_map<position, int>& get_blocks();
    void place_block(glm::ivec3 pos, int block_id);
    void remove_block(glm::ivec3 pos);
};
