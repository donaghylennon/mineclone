#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"

Shader::Shader(const char *vert_path, const char *frag_path) {
    std::ifstream vert_file(vert_path);
    std::ifstream frag_file(frag_path);
    std::stringstream vert_stream, frag_stream;
    vert_stream << vert_file.rdbuf();
    frag_stream << frag_file.rdbuf();
    std::string vert_source_str = vert_stream.str();
    std::string frag_source_str = frag_stream.str();
    const char *vert_source = vert_source_str.c_str();
    const char *frag_source = frag_source_str.c_str();

    unsigned int vertex, fragment;
    int success;
    char log_buffer[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vert_source, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, log_buffer);
        std::cout << "Vertex shader compilation failed:\n" << log_buffer << std::endl;
        exit(1);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &frag_source, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, log_buffer);
        std::cout << "Fragment shader compilation failed:\n" << log_buffer << std::endl;
        exit(1);
    }

    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    glLinkProgram(this->id);

    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->id, 512, NULL, log_buffer);
        std::cout << "Shader program link failed:\n" << log_buffer << std::endl;
        exit(1);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(this->id);
}

void Shader::use() {
    glUseProgram(this->id);
}

void Shader::set_float(std::string name, float value) {
    int location = glGetUniformLocation(this->id, name.c_str());
    if (location < 0) {
        std::cout << "Uniform does not exist at location: " << name << std::endl;
        exit(1);
    }
    glUniform1f(location, value);
}

void Shader::set_mat4(std::string name, glm::mat4& value) {
    int location = glGetUniformLocation(this->id, name.c_str());
    if (location < 0) {
        std::cout << "Uniform does not exist at location: " << name << std::endl;
        exit(1);
    }
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}
