#ifndef HEXAGONBOARD_HPP
#define HEXAGONBOARD_HPP

#include <vector>
#include <map>
#include "Hexagon.hpp"


class HexagonBoard {
private:
    sf::Color unactiveOutlineColor = sf::Color(128, 0, 128);
    sf::Color activeOutlineColorFirstCircle = sf::Color(122, 235, 52);
    sf::Color activeOutlineColorSecondCircle = sf::Color(255, 225, 0);

    std::map<std::pair<int, int>, Hexagon> hexagons;

    void initHexxagonMap(sf::RenderWindow &window);
    void markHexagonsUnavailable(sf::RenderWindow &window, const std::vector<std::pair<int, int> > &positions);

    void selectHexagon(sf::Vector2f clickPosition);
    void processMove(sf::Vector2f clickPosition);
    void resetPreviousSelection();
    void highlightAvailableMoves();
    void handleMoveFirstNeighbor(Hexagon& targetHex);
    void handleMoveSecondNeighbor(Hexagon& targetHex);
    void captureEnemyNeighbors(Hexagon& targetHex);
    void resetColor();

    std::pair<int, int> selectedHexagonPos = {-1, -1};
    int currentPlayerPvP = 1;
    int enemyNumberPvP = 2;

public:
    HexagonBoard(sf::RenderWindow &window);

    void handleClick(sf::Vector2f clickPosition);

    void draw(sf::RenderWindow &window);

    void initPvpStartPosition(int player1, int player2);

    void switchPlayerPvP();

    void switchEnemyNumberPvP();
};
#endif // HEXAGONBOARD_HPP
