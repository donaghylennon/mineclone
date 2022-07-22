#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Direction {
    LEFT, RIGHT, FORWARD, BACKWARD
};

class Camera {
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 world_up;
    float pitch;
    float yaw;
    glm::mat4 view;
public:
    Camera(glm::vec3 position);
    void translate(glm::vec3 direction);
    void move(Direction d, float distance);
    void rotate(float x, float y);
    void update();
    glm::mat4 get_view();
};
