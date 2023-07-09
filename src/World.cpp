#include "World.h"

World::World() {
    this->map.insert(position(0,0,0));
    this->map.insert(position(1,0,0));
    this->map.insert(position(0,0,1));

    this->map.insert(position(-1,0,0));
}

std::unordered_set<position>& World::get_blocks() {
    return this->map;
}

void World::place_block(glm::vec3 pos) {
    this->map.insert(pos);
}
