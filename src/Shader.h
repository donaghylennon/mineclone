#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Shader {
private:
    unsigned int id;

public:
    Shader(const char *vert_path, const char *frag_path);
    ~Shader();
    void use();
    void set_float(std::string name, float value);
    void set_vec3(std::string name, glm::vec3 value);
    void set_mat4(std::string name, glm::mat4& value);
};
