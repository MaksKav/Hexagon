#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "Button.hpp"

class Menu {
private:
    float menuWidth;
    float menuHeight;
    sf::RectangleShape background;
    sf::Font nameFont;
    sf::Text titleText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Button startGameButton;
    Button pvpButton;
    Button pvcButton;
    void loadResources();

public:
    Menu(sf::RenderWindow& window);
    void handleEvent(sf::RenderWindow& window ,const sf::Event& event);
    void draw(sf::RenderWindow& window);

};

#endif