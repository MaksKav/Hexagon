#include "HexagonBoard.hpp"

#include <iostream>

#include "Hexagon.hpp"
#include <valarray>

HexagonBoard::HexagonBoard(sf::RenderWindow &window) {
    initHexxagonMap(window);
}


void HexagonBoard::initHexxagonMap(sf::RenderWindow &window) {
    auto rows = 9;
    auto cols = 5;
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
    // Если еще не выбран гексагон, выбираем его
    if (selectedHexagonPos == std::make_pair(-1, -1)) {
        selectHexagon(clickPosition);
    }
    // Если выбран гексагон, то проверяем возможные ходы
    else {
        processMove(clickPosition);
    }
}

// Метод для обработки выбора клетки
void HexagonBoard::selectHexagon(sf::Vector2f clickPosition) {
    for (auto &[position, hexagon]: hexagons) {
        if (hexagon.contains(clickPosition) && hexagon.getOwner() == currentPlayerPvP) {
            // Сбрасываем предыдущее выделение
            if (selectedHexagonPos != std::make_pair(-1, -1) && hexagons.contains(selectedHexagonPos)) {
                resetPreviousSelection();
            }

            // Устанавливаем новое выделение
            selectedHexagonPos = position;
            hexagon.setOutlineColor(activeOutlineColorSecondCircle);

            // Подсвечиваем соседние клетки, на которые можно сделать ход
            highlightAvailableMoves();
        }
    }
}

void HexagonBoard::processMove(sf::Vector2f clickPosition) {
    for (auto &[position, hexagon]: hexagons) {
        // Если клик на гексагон текущего игрока, переизбираем его
        if (hexagon.contains(clickPosition) && hexagon.getOwner() == currentPlayerPvP) {
            resetPreviousSelection();  // Сброс выделения
            selectedHexagonPos = position;  // Новый выбор
            hexagon.setOutlineColor(activeOutlineColorSecondCircle);  // Выделяем новый
            highlightAvailableMoves();  // Подсвечиваем доступные ходы
            return;  // Завершаем обработку
        }

        // Если клик на пустой гексагон, пытаемся обработать ход
        if (hexagon.contains(clickPosition) && hexagon.getOwner() == 0 && selectedHexagonPos != std::make_pair(-1, -1)) {
            Hexagon &selectedHex = hexagons[selectedHexagonPos];
            Hexagon &targetHex = hexagons[position];

            auto currentHexNeighborsFirst = selectedHex.getFirstNeighborsPos();
            auto currentHexNeighborsSecond = selectedHex.getSecondNeighborsPos();

            if (std::find(currentHexNeighborsFirst.begin(), currentHexNeighborsFirst.end(), targetHex.getPosition()) != currentHexNeighborsFirst.end()) {
                handleMoveFirstNeighbor(targetHex);
            } else if (std::find(currentHexNeighborsSecond.begin(), currentHexNeighborsSecond.end(), targetHex.getPosition()) != currentHexNeighborsSecond.end()) {
                handleMoveSecondNeighbor(targetHex);
            }
        }
    }
}

/*void HexagonBoard::processMove(sf::Vector2f clickPosition) {
    for (auto &[position, hexagon]: hexagons) {
        if (hexagon.contains(clickPosition) && hexagon.getOwner() == 0 && selectedHexagonPos != std::make_pair(-1, -1)) {
            // Получаем текущую выбранную клетку
            Hexagon& selectedHex = hexagons[selectedHexagonPos];
            Hexagon& targetHex = hexagons[position];

            // Проверяем, является ли клетка соседней
            auto currentHexNeighborsFirst = hexagons[selectedHexagonPos].getFirstNeighborsPos();
            auto currentHexNeighborsSecond = hexagons[selectedHexagonPos].getSecondNeighborsPos();

            if (std::find(currentHexNeighborsFirst.begin(), currentHexNeighborsFirst.end(), targetHex.getPosition()) != currentHexNeighborsFirst.end()) {
                handleMoveFirstNeighbor(targetHex);
            }
            else if (std::find(currentHexNeighborsSecond.begin(), currentHexNeighborsSecond.end(), targetHex.getPosition()) != currentHexNeighborsSecond.end()) {
                handleMoveSecondNeighbor(targetHex);
            }
        }
    }
}*/

// Метод для обработки перемещения на первый сосед
void HexagonBoard::handleMoveFirstNeighbor(Hexagon& targetHex) {
    captureEnemyNeighbors(targetHex);

    targetHex.setOwner(currentPlayerPvP);

    // Сбрасываем выбранную клетку и переключаем игрока
    selectedHexagonPos = {-1, -1};
    switchPlayerPvP();
    switchEnemyNumberPvP();
    resetColor();
}


// Метод для обработки перемещения на второй сосед
void HexagonBoard::handleMoveSecondNeighbor(Hexagon& targetHex) {
    captureEnemyNeighbors(targetHex);

    targetHex.setOwner(currentPlayerPvP);
    // Освобождаем предыдущую клетку
    hexagons[selectedHexagonPos].setOwner(0);

    // Сбрасываем выбранную клетку и переключаем игрока
    selectedHexagonPos = {-1, -1};
    switchPlayerPvP();
    switchEnemyNumberPvP();
    resetColor();
}


void HexagonBoard::resetPreviousSelection() {
    Hexagon &prevHex = hexagons[selectedHexagonPos];
    prevHex.setOutlineColor(unactiveOutlineColor);
    auto prevNeighborsFirst = prevHex.getFirstNeighborsPos();
    auto prevNeighborsSecond = prevHex.getSecondNeighborsPos();

    for (auto &neighbor: prevNeighborsFirst) {
        hexagons[neighbor].setOutlineColor(unactiveOutlineColor);
    }
    for (auto &neighbor: prevNeighborsSecond) {
        hexagons[neighbor].setOutlineColor(unactiveOutlineColor);
    }
}

void HexagonBoard::highlightAvailableMoves() {
    auto neighborsFirst = hexagons[selectedHexagonPos].getFirstNeighborsPos();
    auto neighborsSecond = hexagons[selectedHexagonPos].getSecondNeighborsPos();

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
}

void HexagonBoard::captureEnemyNeighbors(Hexagon& targetHex) {
    std::vector<std::pair<int, int>> targetHexFirstNeighbors = targetHex.getFirstNeighborsPos();
    for (const auto& pos : targetHexFirstNeighbors) {
        if (hexagons[pos].getOwner() == enemyNumberPvP) {
            hexagons[pos].setOwner(currentPlayerPvP);
        }
    }
}

void HexagonBoard::resetColor() {
    for (auto &[position, hexagon]: hexagons) {
        hexagon.setOutlineColor(unactiveOutlineColor);
    }
};


void HexagonBoard::switchPlayerPvP() {
    currentPlayerPvP = (currentPlayerPvP == 1) ? 2 : 1;
}

void HexagonBoard::switchEnemyNumberPvP() {
    enemyNumberPvP = (enemyNumberPvP == 2) ? 1 : 2;
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
    for (const auto &pos: positionsPlayer1) {
        auto it = hexagons.find(pos);
        if (it != hexagons.end()) {
            it->second.setOwner(player1);
        }
    }
}
