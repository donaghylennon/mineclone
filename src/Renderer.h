#pragma once

#include "Shader.h"
#include "World.h"
#include "Camera.h"
#include "Model.h"

struct BlockTextureData {
    unsigned int textures[6];
    unsigned int num_textures;
    unsigned int face_textures[6];
};

class CubeRenderer {
private:
    Model cube_model;
    std::vector<BlockTextureData> block_data;
    Shader shader;

public:
    CubeRenderer();
    void draw(position pos, int block_id, Camera *camera, bool highlighted);
};

class Renderer {
private:
    CubeRenderer *cube_renderer;

public:
    Renderer(int width, int height);
    ~Renderer();
    void set_viewport(int width, int height);
    void clear();
    void draw(World *world, Camera *camera);
};
