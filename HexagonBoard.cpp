#include "HexagonBoard.hpp"

#include <iostream>
#include "Hexagon.hpp"
#include <valarray>


HexagonBoard::HexagonBoard(sf::RenderWindow &window):
    scoreButtonPvP(500, 150, "First player: \nSecond player:", font, sf::Color(0,0,0,60), sf::Color::Black, 0) {
    font.loadFromFile("C:\\Users\\Maks\\CLionProjects\\Hexxagon\\resources\\fonts\\Jersey15-Regular.ttf");
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


void HexagonBoard::draw(sf::RenderWindow &window) {
    initScoreButtonPvP(window);
    scoreButtonPvP.draw(window);
    markHexagonsUnavailable(window, {{3, 4}, {4, 3}, {5, 4}});
    for (auto &hexagonPair: hexagons) {
        hexagonPair.second.draw(window);
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
            resetPreviousSelection(); // Сброс выделения
            selectedHexagonPos = position; // Новый выбор
            hexagon.setOutlineColor(activeOutlineColorSecondCircle); // Выделяем новый
            highlightAvailableMoves(); // Подсвечиваем доступные ходы
            return; // Завершаем обработку
        }

        // Если клик на пустой гексагон, пытаемся обработать ход
        if (hexagon.contains(clickPosition) && hexagon.getOwner() == 0 && selectedHexagonPos !=
            std::make_pair(-1, -1)) {
            Hexagon &selectedHex = hexagons[selectedHexagonPos];
            Hexagon &targetHex = hexagons[position];

            auto currentHexNeighborsFirst = selectedHex.getFirstNeighborsPos();
            auto currentHexNeighborsSecond = selectedHex.getSecondNeighborsPos();

            if (std::find(currentHexNeighborsFirst.begin(), currentHexNeighborsFirst.end(), targetHex.getPosition()) !=
                currentHexNeighborsFirst.end()) {
                handleMoveFirstNeighbor(targetHex);
            } else if (std::find(currentHexNeighborsSecond.begin(), currentHexNeighborsSecond.end(),
                                 targetHex.getPosition()) != currentHexNeighborsSecond.end()) {
                handleMoveSecondNeighbor(targetHex);
            }
        }
    }
}


// Метод для обработки перемещения на первый сосед
void HexagonBoard::handleMoveFirstNeighbor(Hexagon &targetHex) {
    captureEnemyNeighbors(targetHex);

    targetHex.setOwner(currentPlayerPvP);

    // Сбрасываем выбранную клетку и переключаем игрока
    selectedHexagonPos = {-1, -1};
    switchPlayerPvP();
    switchEnemyNumberPvP();
    resetColor();
}


// Метод для обработки перемещения на второй сосед
void HexagonBoard::handleMoveSecondNeighbor(Hexagon &targetHex) {
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

void HexagonBoard::captureEnemyNeighbors(Hexagon &targetHex) {
    std::vector<std::pair<int, int> > targetHexFirstNeighbors = targetHex.getFirstNeighborsPos();
    for (const auto &pos: targetHexFirstNeighbors) {
        if (hexagons[pos].getOwner() == enemyNumberPvP) {
            hexagons[pos].setOwner(currentPlayerPvP);
        }
    }
}

void HexagonBoard::resetColor() {
    for (auto &[position, hexagon]: hexagons) {
        hexagon.setOutlineColor(unactiveOutlineColor);
    }
}




void HexagonBoard::switchPlayerPvP() {
    currentPlayerPvP = (currentPlayerPvP == 1) ? 2 : 1;
}

void HexagonBoard::switchEnemyNumberPvP() {
    enemyNumberPvP = (enemyNumberPvP == 2) ? 1 : 2;
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

void HexagonBoard::initScoreButtonPvP(sf::RenderWindow &window) {
    scoreButtonPvP.setTextPos(window , 0,0);
    scoreButtonPvP.setTextColor(sf::Color::White);
    float byX = window.getSize().x  - scoreButtonPvP.getShape().getSize().x  - 50 ;
    auto player1Score = player1ScoreCount();
    auto player2Score = player2ScoreCount();
    std::string scoreText = "First player:  " + std::to_string(player1Score) + "\nSecond player: " + std::to_string(player2Score);
    scoreButtonPvP.setText(scoreText);
    scoreButtonPvP.setPosition(window, byX, 20, scoreText);

}

int HexagonBoard::player1ScoreCount() {
    auto count = 0 ;
    for (auto &hexagon: hexagons) {
        if (hexagon.second.getOwner() == 1) {
            count+=1;
        }
    }
    return count;
}

int HexagonBoard::player2ScoreCount() {
    auto count = 0 ;
    for (auto &hexagon: hexagons) {
        if (hexagon.second.getOwner() == 2) {
            count+=1;
        }
    }
    return count;
}


