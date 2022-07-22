#pragma once

#include "Shader.h"
#include "World.h"

class CubeRenderer {
private:
    unsigned int vao;
    unsigned int vbo;
    Shader shader;

public:
    CubeRenderer();
    ~CubeRenderer();
    void draw(position pos);
};

class Renderer {
private:
    CubeRenderer *cube_renderer;

public:
    Renderer(int width, int height);
    ~Renderer();
    void set_viewport(int width, int height);
    void clear();
    void draw(World *world);
};
