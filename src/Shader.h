#pragma once

#include <string>

class Shader {
private:
    unsigned int id;

public:
    Shader(const char *vert_path, const char *frag_path);
    ~Shader();
    void use();
    void set_float(std::string name, float value);
};
