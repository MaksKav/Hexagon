#ifndef HEXAGONBOARD_HPP
#define HEXAGONBOARD_HPP

#include <vector>
#include "Hexagon.hpp"

class HexagonBoard {
private:
    std::map<std::pair<int,int> , Hexagon> hexagons;

    void initHexxagonMap(sf::RenderWindow& window);
    void markHexagonsUnavailable(sf::RenderWindow &window, const std::vector<std::pair<int, int>> &positions);
public:
    HexagonBoard(sf::RenderWindow& window);

    void draw(sf::RenderWindow& window);
};

#endif // HEXAGONBOARD_HPP

