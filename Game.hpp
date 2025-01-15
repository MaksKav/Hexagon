#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Menu.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    Menu menu;

    enum class GameState { Menu, Playing };
    GameState state;

public:
    Game();
    void run(); // Главный игровой цикл
    void loadResources();
};

#endif // GAME_H
