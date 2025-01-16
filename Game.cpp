#include "Game.hpp"

Game::Game()
    : window(sf::VideoMode(1800, 1400), "Hexxagon"),
      menu(window),
      state(GameState::Menu) {
    loadResources();
}

void Game::run() {
    sf::Image cursorImage;
    cursorImage.loadFromFile("C:\\Users\\Maks\\CLionProjects\\Hexxagon\\resources\\icon_cursor.png");
    sf::Vector2u clickSpot(15, 7);
    sf::Cursor cursor;
    cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), clickSpot);
    window.setMouseCursor(cursor);

    sf::Event event;
    while (window.isOpen()) {
        window.clear();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (state == GameState::Menu) {
                menu.handleEvent(window , event);
            }
        }

        window.draw(backgroundSprite);
        if (state == GameState::Menu) {
            menu.draw(window);
        } else if (state == GameState::Playing) {

        }
        window.display();
    }
}

void Game::loadResources() {
    if (!backgroundTexture.loadFromFile("C:\\Users\\Maks\\CLionProjects\\Hexxagon\\resources\\stars.jpg")) {
        throw std::runtime_error("Can't load the background texture");
    }
    backgroundSprite.setTexture(backgroundTexture);
}




