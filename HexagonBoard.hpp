#ifndef HEXAGONBOARD_HPP
#define HEXAGONBOARD_HPP

#include <vector>
#include <map>
#include "Hexagon.hpp"


class HexagonBoard {
private:
    std::map<std::pair<int,int> , Hexagon> hexagons;

    void initHexxagonMap(sf::RenderWindow& window);
    void markHexagonsUnavailable(sf::RenderWindow &window, const std::vector<std::pair<int, int>> &positions);

    std::pair<int, int> selectedHexagon = {-1, -1};
public:
    HexagonBoard(sf::RenderWindow& window);

    void draw(sf::RenderWindow& window);
    void initPvpStartPosition(int player1 , int player2);

    void handleClick(sf::Vector2f clickPosition);
};
#endif // HEXAGONBOARD_HPP

