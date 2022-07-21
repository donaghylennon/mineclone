#pragma once

#include <unordered_set>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

using position = glm::vec3;

class World {
private:
    //std::unordered_map<position, Block> map;
    std::unordered_set<position> map;
public:
    World();
};
