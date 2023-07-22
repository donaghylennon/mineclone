#pragma once

#include "Shader.h"
#include "World.h"
#include "Camera.h"

struct BlockTextureData {
    unsigned int textures[6];
    unsigned int num_textures;
    unsigned int face_textures[6];
};

class CubeRenderer {
private:
    unsigned int vao;
    unsigned int vbo;
    std::vector<BlockTextureData> block_data;
    Shader shader;

public:
    CubeRenderer();
    ~CubeRenderer();
    void draw(position pos, unsigned int block_id, Camera *camera, bool highlighted);
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
