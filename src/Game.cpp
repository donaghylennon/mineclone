#include "Game.h"

Game::Game() {
    this->window = new Window(800, 600);
    this->renderer = new Renderer(800, 600);
    this->window->set_callback_renderer(this->renderer);
    this->world = new World();
}

Game::~Game() {
    delete this->window;
    delete this->renderer;
    delete this->world;
}

void Game::loop() {
    while (!this->window->should_close()) {
        float current_frame_time = this->window->get_time();
        this->delta_time = current_frame_time - this->last_frame_time;
        this->last_frame_time = current_frame_time;

        this->renderer->clear();

        this->renderer->draw(this->world);

        this->window->swap_buffers();
        this->window->poll_events();
    }
}
