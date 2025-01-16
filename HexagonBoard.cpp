#include "HexagonBoard.hpp"
#include "Hexagon.hpp"
#include <valarray>

HexagonBoard::HexagonBoard(sf::RenderWindow &window) {
 initHexxagonMap(window);
}


void HexagonBoard::initHexxagonMap(sf::RenderWindow& window) {
    auto rows = 9;
    auto cols = 5;
    auto counter = 0;
    for (auto row = 0; row < rows; row++) {
        for (auto col = 0; col < cols; col++) {
            hexagons.emplace(std::make_pair(row, col), Hexagon(window, row, col));
        }
        if (row < 4) {
            cols += 1;
        } else {
            cols -= 1;
        }
    }
};


void HexagonBoard::draw(sf::RenderWindow &window) {
    markHexagonsUnavailable(window, {{3, 4}, {4, 3}, {5, 4}});
    for (auto &hexagonPair: hexagons) {
        hexagonPair.second.draw(window);
    }
}

void HexagonBoard::markHexagonsUnavailable(sf::RenderWindow &window, const std::vector<std::pair<int, int>> &positions) {
    for (const auto &pos : positions) {
        auto it = hexagons.find(pos);
        if (it != hexagons.end()) {
            it->second.installUnavailableHexagon(window);
        }
    }
}
