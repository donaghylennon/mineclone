#include "Game.h"
#include <optional>

Game::Game() {
    this->window = new Window(1400, 900);
    this->renderer = new Renderer(1400, 900);
    this->window->set_user_pointer(this);
    this->world = new World();
    this->camera = new Camera(glm::vec3(0.5f, 2.5f, 3.5f));
}

Game::~Game() {
    delete this->window;
    delete this->renderer;
    delete this->world;
    delete this->camera;
}

Camera *Game::get_camera() {
    return this->camera;
}

Renderer *Game::get_renderer() {
    return this->renderer;
}

void Game::loop() {
    while (!this->window->should_close()) {
        float current_frame_time = this->window->get_time();
        this->delta_time = current_frame_time - this->last_frame_time;
        this->last_frame_time = current_frame_time;

        this->renderer->clear();

        this->renderer->draw(this->world, this->camera);

        this->window->process_input(this->camera, this->world);

        this->window->swap_buffers();
        this->window->poll_events();
    }
}
