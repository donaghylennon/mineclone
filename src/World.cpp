#include "stb_perlin.h"

#include "World.h"

World::World() {
    for (int i = -10; i <= 10; i++) {
        for (int j = -10; j <= 10; j++) {
            int height = ceil(20*stb_perlin_noise3(i*0.02, j*0.02, 0, 0, 0, 0));
            for (int y = -11; y < height; y++) {
                if (y == height-1)
                    this->map.insert({position(i,y,j), 1});
                else
                    this->map.insert({position(i,y,j), 0});
            }
        }
    }
}

std::unordered_map<position, int>& World::get_blocks() {
    return this->map;
}

void World::place_block(glm::ivec3 pos, int block_id) {
    this->map.insert({pos, block_id});
}

void World::remove_block(glm::ivec3 pos) {
    this->map.erase(pos);
}
