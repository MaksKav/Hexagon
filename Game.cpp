#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(1800, 1400), "Hexxagon"),
      menu(window),
      state(GameState::Menu) {
    loadResources();
}

void Game::loadResources() {
    if (!backgroundTexture.loadFromFile("C:\\Users\\Maks\\CLionProjects\\Hexxagon\\resources\\stars.jpg")) {
        throw std::runtime_error("Can't load the background texture");
    }
    backgroundSprite.setTexture(backgroundTexture);

}

void Game::run() {
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (state == GameState::Menu) {
                menu.handleEvent(event);
            }
        }

        window.clear();
        window.draw(backgroundSprite);
       // menu.draw(window);
        if (state == GameState::Menu) {
            menu.draw(window);
        } else if (state == GameState::Playing) {
        }
        window.display();
    }
}
