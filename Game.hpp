#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "HexagonBoard.hpp"
#include "Menu.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    Menu menu;
    HexagonBoard board;


public:
    Game();
    enum class GameState { Menu, Playing };
    static GameState state;

    void run(); // Главный игровой цикл
    void loadResources();

    static void setState(GameState newState);
};

#endif // GAME_H
