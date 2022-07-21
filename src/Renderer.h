#pragma once

#include "Shader.h"

class CubeRenderer {
private:
    unsigned int vao;
    unsigned int vbo;
    Shader shader;

public:
    CubeRenderer();
    ~CubeRenderer();
    void draw();
};

class Renderer {
private:
    CubeRenderer *cube_renderer;

public:
    Renderer(int width, int height);
    ~Renderer();
    void set_viewport(int width, int height);
    void draw();
};
