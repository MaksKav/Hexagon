#include "Menu.hpp"

#include <iostream>

#include "Game.hpp"

Menu::Menu(sf::RenderWindow &window)
    : menuWidth(window.getSize().x * 0.8f),
      menuHeight(window.getSize().y * 0.8f),
      startGameButton(700.f, 70.f, "START GAME", nameFont, sf::Color(255, 255, 255, 90), sf::Color::Black, 5.f),
      pvpButton(700.f, 70.f, "PLAYER vs. PLAYER", nameFont, sf::Color(255, 255, 255, 90), sf::Color::Black, 5.f),
      pvcButton(700.f, 70.f, "PLAYER vs. COMPUTER", nameFont, sf::Color(255, 255, 255, 90), sf::Color::Black, 5.f) {
    loadResources();

    startGameButton.setPosition(window, (window.getSize().x - 700.f) / 2, menuHeight);

    auto playButtonGlobalPosition = startGameButton.getGlobalPosition();
    pvpButton.setPosition(window, playButtonGlobalPosition.x, playButtonGlobalPosition.y - 150);

    auto pvpButtonGlobalPosition = pvpButton.getGlobalPosition();
    pvcButton.setPosition(window, playButtonGlobalPosition.x, pvpButtonGlobalPosition.y - 100);
}

void Menu::loadResources() {
    if (!nameFont.loadFromFile("C:\\Users\\Maks\\CLionProjects\\Hexxagon\\resources\\fonts\\Jersey15-Regular.ttf")) {
        throw std::runtime_error("Can't load the font");
    }
    titleText.setFont(nameFont);
    titleText.setCharacterSize(250);
    titleText.setString("H E X X A G O N");
    titleText.setFillColor(sf::Color(255, 215, 0)); // gold color
}


void Menu::handleEvent(sf::RenderWindow &window, const sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (startGameButton.isClicked(window, sf::Mouse::Left)) {
            Game::state = Game::GameState::Playing;
        }

        if (pvpButton.isClicked(window, sf::Mouse::Left)) {
            pvpButton.useActiveColor();
            pvpButton.setClickedFlag(true);
            Game::mode = Game::GameMode::PvP;

            pvcButton.useInactiveColor();
            pvcButton.setClickedFlag(false);
        }

        if (pvcButton.isClicked(window, sf::Mouse::Left)) {
            pvcButton.useActiveColor();
            pvcButton.setClickedFlag(true);
            Game::mode = Game::GameMode::PvC;

            pvpButton.useInactiveColor();
            pvpButton.setClickedFlag(false);
        }
    }

    if (startGameButton.isMouseOver(window)) {
        startGameButton.useActiveColor();
    } else {
        startGameButton.useInactiveColor();
    }

    if (pvpButton.getClickedFlag() == false) {
        if (pvpButton.isMouseOver(window)) {
            pvpButton.useActiveColor();
        } else {
            pvpButton.useInactiveColor();
        }
    }

    if (pvcButton.getClickedFlag() == false) {
        if (pvcButton.isMouseOver(window)) {
            pvcButton.useActiveColor();
        } else {
            pvcButton.useInactiveColor();
        }
    }
}


void Menu::draw(sf::RenderWindow &window) {
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    float menuWidth = windowWidth * 0.8f;
    float menuHeight = windowHeight * 0.8f;

    background.setSize(sf::Vector2f(menuWidth, menuHeight));
    background.setFillColor(sf::Color(50, 0, 80, 70));
    background.setPosition(sf::Vector2f((windowWidth - menuWidth) / 2, (windowHeight - menuHeight) / 2));

    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setPosition((windowWidth - textRect.width) / 2, -10);

    window.draw(background);
    window.draw(titleText);

    startGameButton.draw(window);
    pvpButton.draw(window);
    pvcButton.draw(window);
}