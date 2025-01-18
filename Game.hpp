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
    HexagonBoard boardPvP;


public:
    Game();
    enum class GameState { Menu , Playing };
    enum class GameMode {None , PvP , PvC} ;
    static GameState state;
    static GameMode mode;

    void run(); // Главный игровой цикл
    void loadResources();

};

#endif // GAME_H