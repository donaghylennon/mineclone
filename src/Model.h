#pragma once

#include <glad/glad.h>

#include <vector>

class Model {
private:
    GLuint vao = 0;
    GLuint vbo = 0;

public:
    void add_data(std::vector<GLfloat> data);
    ~Model();
    void bind_vao();
};
