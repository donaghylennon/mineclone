#include "Game.h"

Game::Game() {
    this->window = new Window(800, 600);
    this->world = new World();
    //this->renderer = new Renderer(800, 600);
}

Game::~Game() {
    delete this->window;
    //delete this->renderer;
}

void Game::loop() {
    window->loop();
}
