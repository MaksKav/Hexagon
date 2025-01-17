#include "HexagonBoard.hpp"
#include "Hexagon.hpp"
#include <valarray>

HexagonBoard::HexagonBoard(sf::RenderWindow &window) {
    initHexxagonMap(window);
}


void HexagonBoard::initHexxagonMap(sf::RenderWindow &window) {
    auto rows = 9;
    auto cols = 5;
    auto counter = 0;
    for (auto row = 0; row < rows; row++) {
        for (auto col = 0; col < cols; col++) {
            Hexagon hex(window, row, col);
            hexagons.emplace(std::make_pair(row, col), hex);
        }
        if (row < 4) {
            cols += 1;
        } else {
            cols -= 1;
        }
    }
};

void HexagonBoard::handleClick(sf::Vector2f clickPosition) {
    sf::Color unactiveOutlineColor = sf::Color(128, 0, 128); // violence
    sf::Color activeOutlineColorFirstCircle = sf::Color(122, 235, 52); //green
    sf::Color activeOutlineColorSecondCircle = sf::Color(255, 225, 0); // orange

    for (auto &[position, hexagon]: hexagons) {
        if (hexagon.contains(clickPosition) && hexagon.getIsAvailable()) {
            if (selectedHexagon != std::make_pair(-1, -1) && hexagons.contains(selectedHexagon)) {
                hexagons[selectedHexagon].setOutlineColor(unactiveOutlineColor);
                auto neighborsFirst = hexagons[selectedHexagon].getFirstNeighborsPos();
                auto neighborsSecond = hexagons[selectedHexagon].getSecondNeighborsPos();
                for (auto &neighbor: neighborsFirst) {
                    hexagons[neighbor].setOutlineColor(unactiveOutlineColor);
                }
                for (auto &neighbor: neighborsSecond) {
                    hexagons[neighbor].setOutlineColor(unactiveOutlineColor);
                }
            }

            // Устанавливаем обводку у текущего гексагона + подсвечиваем возможные хода
            selectedHexagon = position;
            hexagon.setOutlineColor(activeOutlineColorSecondCircle);
            auto neighborsFirst = hexagon.getFirstNeighborsPos();
            auto neighborsSecond = hexagon.getSecondNeighborsPos();
            for (auto &neighbor: neighborsFirst) {
                if (hexagons[neighbor].getOwner() == 0) {
                    hexagons[neighbor].setOutlineColor(activeOutlineColorFirstCircle);
                }
            }
            for (auto &neighbor: neighborsSecond) {
                if (hexagons[neighbor].getOwner() == 0) {
                    hexagons[neighbor].setOutlineColor(activeOutlineColorSecondCircle);
                }
            }
            return;
        }
    }
}


void HexagonBoard::draw(sf::RenderWindow &window) {
    markHexagonsUnavailable(window, {{3, 4}, {4, 3}, {5, 4}});
    for (auto &hexagonPair: hexagons) {
        hexagonPair.second.draw(window);
    }
}

void HexagonBoard::markHexagonsUnavailable(sf::RenderWindow &window,
                                           const std::vector<std::pair<int, int> > &positions) {
    for (const auto &pos: positions) {
        auto it = hexagons.find(pos);
        if (it != hexagons.end()) {
            it->second.installUnavailableHexagon(window);
        }
    }
}

void HexagonBoard::initPvpStartPosition(int player1, int player2) {
    const std::vector<std::pair<int, int> > positionsPlayer1 = {{0, 4}, {4, 0}, {8, 4}};
    const std::vector<std::pair<int, int> > positionsPlayer2 = {{0, 0}, {8, 0}, {4, 8}};
    for (const auto &pos: positionsPlayer2) {
        auto it = hexagons.find(pos);
        if (it != hexagons.end()) {
            it->second.setOwner(player2);
        }
    }
    for (const auto &pos: positionsPlayer1
    ) {
        auto it = hexagons.find(pos);
        if (it != hexagons.end()) {
            it->second.setOwner(player1);
        }
    }
}
