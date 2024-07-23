#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include <iostream>

#include "Renderer.h"
#include "Model.h"

Renderer::Renderer(int width, int height) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD" << std::endl;
        exit(1);
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glViewport(0, 0, width, height);

    this->cube_renderer = new CubeRenderer();
}

Renderer::~Renderer() {
    delete this->cube_renderer;
}

void Renderer::set_viewport(int width, int height) {
    glViewport(0, 0, width, height);
}

void Renderer::clear() {
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(World *world, Camera *camera) {
    auto faced_block = camera->get_faced_block_pos(world);

    bool player_is_facing_block = false;
    if (faced_block.has_value())
        player_is_facing_block = true;

    for (const auto& entry : world->get_blocks())
        this->cube_renderer->draw(entry.first, entry.second, camera,
                player_is_facing_block && entry.first == *faced_block);
}

CubeRenderer::CubeRenderer()
    : shader(Shader("res/cube_shader.vert", "res/cube_shader.frag")) {
    cube_model.add_data({
        // positions          // normals           // texture coords
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    });

    stbi_set_flip_vertically_on_load(true);
    int width, height, num_components;
    unsigned char *data = stbi_load("res/cube.png", &width, &height, &num_components, 0);
    if (!data) {
        std::cout << "Failed to load texture" << std::endl;
        exit(1);
    }
    
    unsigned int texture0, texture1, texture2;
    glGenTextures(1, &texture0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
            data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    data = nullptr;
    this->block_data.push_back({{texture0}, 1, {0, 0, 0, 0, 0, 0}});

    BlockTextureData grass = {{0, 0, 0, 0, 0, 0}, 3, {1, 1, 1, 1, 0, 2}};
    grass.textures[0] = texture0;

    data = stbi_load("res/grass1.png", &width, &height, &num_components, 0);
    if (!data) {
        std::cout << "Failed to load texture" << std::endl;
        exit(1);
    }
    
    glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
            data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    data = nullptr;
    grass.textures[1] = texture1;

    data = stbi_load("res/grass2.png", &width, &height, &num_components, 0);
    if (!data) {
        std::cout << "Failed to load texture" << std::endl;
        exit(1);
    }
    
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
            data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    data = nullptr;
    grass.textures[2] = texture2;
    this->block_data.push_back(grass);
}

void CubeRenderer::draw(position pos, int block_id, Camera *camera,
        bool highlighted) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 real_pos = pos;
    model = glm::translate(model, real_pos + glm::vec3(0.5f, 0.5f, 0.5f));

    glm::mat4 view = camera->get_view();

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 1400.0f / 900.0f, 0.1f, 100.0f);

    auto block_data = this->block_data[block_id];
    cube_model.bind_vao();
    for (int i = 0; i < 6; i++) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,
                block_data.textures[block_data.face_textures[i]]);

        this->shader.use();
        this->shader.set_mat4("model", model);
        this->shader.set_mat4("view", view);
        this->shader.set_mat4("projection", projection);
        if (highlighted) {
            this->shader.set_float("highlight", 0.2f);
        } else {
            this->shader.set_float("highlight", 0.0f);
        }
        glDrawArrays(GL_TRIANGLES, i*6, 6);
    }
}
