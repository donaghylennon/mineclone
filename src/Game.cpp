#include "Game.h"
#include "Camera.h"
#include "Player.h"
#include <optional>

Game::Game() {
    this->window = new Window(1400, 900);
    this->renderer = new Renderer(1400, 900);
    this->window->set_user_pointer(this);
    this->world = new World();
    this->player = new Player(glm::vec3(0.5f, 1.5f, 3.5f));
    this->camera = new Camera(*this->player);
}

Game::~Game() {
    delete this->window;
    delete this->renderer;
    delete this->world;
    delete this->camera;
    delete this->player;
}

World *Game::get_world() {
    return this->world;
}

Player *Game::get_player() {
    return this->player;
}

Camera *Game::get_camera() {
    return this->camera;
}

Renderer *Game::get_renderer() {
    return this->renderer;
}

void Game::loop() {
    float frame_time = 1.0f/60.0f;
    while (!this->window->should_close()) {
        float current_frame_time = this->window->get_time();
        this->delta_time = current_frame_time - this->last_frame_time;

        if (current_frame_time >= frame_time) {
            this->last_frame_time = current_frame_time;
            this->renderer->clear();

            this->renderer->draw(this->world, this->camera);

            this->window->process_input(this);
            this->camera->update();

            this->window->swap_buffers();
            this->window->poll_events();
        }

    }
}
