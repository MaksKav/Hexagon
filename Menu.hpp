#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
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
    std::vector<Button> buttons;
    void loadResources();
    void initMenuButtons(sf::RenderWindow& window);
public:
    Menu(sf::RenderWindow& window);
    void addButton(const Button& button);
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window);
};

#endif


