#include "HexagonBoard.hpp"

#include <valarray>
#include "Game.hpp"


HexagonBoard::HexagonBoard(sf::RenderWindow &window): window(window),
                                                      scoreButtonPvP(500, 150, "First player: \nSecond player:", font,
                                                                     sf::Color(0, 0, 0, 60), sf::Color::Black, 0) {
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
    if (selectedHexagonPos == std::make_pair(-1, -1)) {
        selectHexagon(clickPosition);
    } else {
        processMove(clickPosition);
    }
}

void HexagonBoard::selectHexagon(sf::Vector2f clickPosition) {
    for (auto &[position, hexagon]: hexagons) {
        if (hexagon.contains(clickPosition) && hexagon.getOwner() == currentPlayerPvP) {
            if (selectedHexagonPos != std::make_pair(-1, -1) && hexagons.contains(selectedHexagonPos)) {
                resetPreviousSelection();
            }

            selectedHexagonPos = position;
            hexagon.setOutlineColor(activeOutlineColorSecondCircle);

            highlightAvailableMoves();
        }
    }
}

void HexagonBoard::processMove(sf::Vector2f clickPosition) {
    for (auto &[position, hexagon]: hexagons) {
        if (hexagon.contains(clickPosition) && hexagon.getOwner() == currentPlayerPvP) {
            resetPreviousSelection();
            selectedHexagonPos = position;
            hexagon.setOutlineColor(activeOutlineColorSecondCircle);
            highlightAvailableMoves();
            return;
        }

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


void HexagonBoard::handleMoveFirstNeighbor(Hexagon &targetHex) {
    captureEnemyNeighbors(targetHex);

    targetHex.setOwner(currentPlayerPvP);

    selectedHexagonPos = {-1, -1};
    switchPlayerPvP();
    switchEnemyNumberPvP();
    resetColor();

    if (checkGameOver()) {
        sf::Texture screenshotTexture;
        screenshotTexture.create(window.getSize().x, window.getSize().y);
        window.display();
        screenshotTexture.update(window);
        endGame(window, screenshotTexture);
    }
}


void HexagonBoard::handleMoveSecondNeighbor(Hexagon &targetHex) {
    captureEnemyNeighbors(targetHex);

    targetHex.setOwner(currentPlayerPvP);
    hexagons[selectedHexagonPos].setOwner(0);

    selectedHexagonPos = {-1, -1};
    switchPlayerPvP();
    switchEnemyNumberPvP();
    resetColor();

    if (checkGameOver()) {
        sf::Texture screenshotTexture;
        screenshotTexture.create(window.getSize().x, window.getSize().y);
        window.display();
        screenshotTexture.update(window);
        endGame(window, screenshotTexture);
    }
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
    scoreButtonPvP.setTextPos(window, 0, 0);
    scoreButtonPvP.setTextColor(sf::Color::White);
    float byX = window.getSize().x - scoreButtonPvP.getShape().getSize().x - 50;
    auto player1Score = player1ScoreCount();
    auto player2Score = player2ScoreCount();
    std::string scoreText = "First player:  " + std::to_string(player1Score) + "\nSecond player: " +
                            std::to_string(player2Score);
    scoreButtonPvP.setText(scoreText);
    scoreButtonPvP.setPosition(window, byX, 20);
}

int HexagonBoard::player1ScoreCount() {
    auto count = 0;
    for (auto &hexagon: hexagons) {
        if (hexagon.second.getOwner() == 1) {
            count += 1;
        }
    }
    return count;
}

int HexagonBoard::player2ScoreCount() {
    auto count = 0;
    for (auto &hexagon: hexagons) {
        if (hexagon.second.getOwner() == 2) {
            count += 1;
        }
    }
    return count;
}


bool HexagonBoard::checkGameOver() {
    if (player1ScoreCount() == 0 || player2ScoreCount() == 0) {
        return true;
    }

    if (player1ScoreCount() + player2ScoreCount() >= 58) {
        return true;
    }

    if (!canPlayerMakeMove(currentPlayerPvP) || !canPlayerMakeMove(enemyNumberPvP)) {
        return true;
    }

    bool allHexagonsOccupied = true;
    for (const auto &[position, hexagon]: hexagons) {
        if (hexagon.getOwner() == 0) {
            allHexagonsOccupied = false;
            break;
        }
    }
    return allHexagonsOccupied;
}

bool HexagonBoard::canPlayerMakeMove(int player) {
    bool canMove = false;
    for (auto &[position, hexagon]: hexagons) {
        if (hexagon.getOwner() == player) {
            auto firstNeighbors = hexagon.getFirstNeighborsPos();
            auto secondNeighbors = hexagon.getSecondNeighborsPos();

            for (auto &neighbor: firstNeighbors) {
                if (hexagons[neighbor].getOwner() == 0) {
                    canMove = true;
                    return canMove;
                }
            }
            for (auto &neighbor: secondNeighbors) {
                if (hexagons[neighbor].getOwner() == 0) {
                    canMove = true;
                    return canMove;
                }
            }
        }
    }
    return canMove;
}

void HexagonBoard::endGame(sf::RenderWindow &window, sf::Texture screenshotTexture) {
    sf::Sprite screenshotSprite(screenshotTexture);

    std::string winner = (player1ScoreCount() > player2ScoreCount()) ? "Player 1" : "Player 2";

    sf::Font font;
    font.loadFromFile("C:\\Users\\Maks\\CLionProjects\\Hexxagon\\resources\\fonts\\Jersey15-Regular.ttf");

    Button gameOverButton(1000, 200, "Game Over " + winner + " wins!", font, sf::Color(0, 0, 0, 90), sf::Color::Black,
                          0);
    gameOverButton.setPosition(window,
                               (window.getSize().x - gameOverButton.getShape().getSize().x) / 2,
                               (window.getSize().y - gameOverButton.getShape().getSize().y) / 2 - 300);
    gameOverButton.setTextColor(sf::Color::White);
    gameOverButton.setTextSize(150);
    gameOverButton.setTextPos(window, gameOverButton.getGlobalBounds().getPosition().x,
                              gameOverButton.getGlobalBounds().getPosition().y);

    Button exitButton(450, 100, "Exit Game", font, sf::Color(0, 0, 0, 255), sf::Color::Red, 3);
    exitButton.setPosition(window,
                           (window.getSize().x - exitButton.getShape().getSize().x) / 2,
                           window.getSize().y / 2 + 320);
    exitButton.setTextColor(sf::Color::White);
    exitButton.setTextSize(75);
    exitButton.setTextPos(window, exitButton.getGlobalBounds().getPosition().x,
                          exitButton.getGlobalBounds().getPosition().y + 10);

    Button menuButton(450, 100, "Back to Menu", font, sf::Color(0, 0, 0, 255), sf::Color::Red, 3);
    menuButton.setPosition(window,
                           (window.getSize().x - menuButton.getShape().getSize().x) / 2,
                           window.getSize().y / 2 + 200);
    menuButton.setTextColor(sf::Color::White);
    menuButton.setTextSize(75);
    menuButton.setTextPos(window, menuButton.getGlobalBounds().getPosition().x,
                          menuButton.getGlobalBounds().getPosition().y + 10);

    bool exitGame = false;
    bool goToMenu = false;

    while (!exitGame && !goToMenu) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (exitButton.isClicked(window, sf::Mouse::Left)) {
                    exitGame = true;
                }
                if (menuButton.isClicked(window, sf::Mouse::Left)) {
                    goToMenu = true;
                }
            }
        }
        window.clear();
        window.draw(screenshotSprite);
        gameOverButton.draw(window);
        exitButton.draw(window);
        menuButton.draw(window);
        window.display();
    }

    if (exitGame) {
        window.close();
    } else if (goToMenu) {
        resetBoard();
        Game::state = Game::GameState::Menu; // Переход в меню
    }
}


void HexagonBoard::resetBoard() {
    for (auto &[position, hexagon]: hexagons) {
        hexagon.setOwner(0);
    }

    initPvpStartPosition(1, 2);

    resetColor();
    selectedHexagonPos = {-1, -1};
    currentPlayerPvP = 1; // Сбрасываем текущего игрока
    enemyNumberPvP = 2;
}
