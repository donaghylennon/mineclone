#include "Model.h"

void Model::add_data(std::vector<GLfloat> data) {
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*data.size(), data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
            (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
            (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
}

Model::~Model() {
    if (vao)
        glDeleteVertexArrays(1, &this->vao);
    if (vbo)
        glDeleteBuffers(1, &this->vbo);
}

void Model::bind_vao() {
    glBindVertexArray(this->vao);
}
