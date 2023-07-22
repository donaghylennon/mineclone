#include "World.h"

World::World() {
    this->map.insert({position(0,0,0), 0});
    this->map.insert({position(1,0,0), 0});
    this->map.insert({position(0,0,1), 0});

    this->map.insert({position(-1,0,0), 0});
    for (int i = -10; i <= 10; i++) {
        for (int j = -10; j <= 10; j++) {
            this->map.insert({position(i,0,j), 0});
        }
    }
}

std::unordered_map<position, int>& World::get_blocks() {
    return this->map;
}

void World::place_block(glm::ivec3 pos) {
    this->map.insert({pos, 0});
}

void World::remove_block(glm::ivec3 pos) {
    this->map.erase(pos);
}
