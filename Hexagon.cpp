#include "Hexagon.hpp"

#include <cmath>
#include <iostream>

const float Hexagon::hexRadius = 70;

Hexagon::Hexagon(sf::RenderWindow &window, int row, int col) {
    this->row = row;
    this->col = col;
    position = {row,col};

    outerHexxagon = sf::CircleShape(hexRadius, 6);
    outerHexxagon.setOutlineThickness(10);
    outerHexxagon.setOutlineColor(sf::Color(0, 0, 0));
    outerHexxagon.setFillColor(sf::Color(128, 60, 128));

    innerHexxagon = sf::CircleShape(hexRadius, 6);
    innerHexxagon.setOutlineThickness(5);
    innerHexxagon.setOutlineColor(sf::Color(128, 0, 128));
    innerHexxagon.setFillColor(sf::Color::Transparent);

    if (!player2Texture.loadFromFile("C:\\Users\\Maks\\CLionProjects\\Hexxagon\\resources\\Aleh.png")) {
        std::cout << "Failed to load Aleh texture";
    }

    if (!player1Texture.loadFromFile("C:\\Users\\Maks\\CLionProjects\\Hexxagon\\resources\\MaksToHex.png")) {
        std::cout << "Failed to load Maks texture";
    }

    getNeighbors(row, col);
    setOuterAndInnerHexxagonPositions(window, row, col);
}


std::vector<std::pair<int, int> > Hexagon::installNeighbors(int row, int col,
                                                            const std::vector<std::pair<int, int> > &vec) {
    std::vector<std::pair<int, int> > v;
    for (const auto &p: vec) {
        int newRow = row + p.first;
        int newCol = col + p.second;

        if (newRow >= 0 && newCol >= 0) {      // to nie usunie wszystkie niepoprawne pary , ale my i tak nie musimy ich usuwac
            v.push_back({newRow, newCol});
        }
    }
    return v;
}


void Hexagon::setOuterAndInnerHexxagonPositions(sf::RenderWindow &window, int row, int col) {
    auto setXPosition = [&](int x) {
        if (x == 1 || x == 7 || x == 2 || x == 6) {
            return hexRadius * 2;
        } else if (x == 3 || x == 5 || x == 4) {
            return 2 * (hexRadius * 2);
        } else
            return 0.f;
    };

    float verticalDistanceOuter = hexRadius * std::sqrt(3);
    float horizontalDistanceOuter = hexRadius * 2;
    auto startPositionX = (window.getSize().x - (9 * horizontalDistanceOuter));
    auto startPositionY = (window.getSize().y - (9 * verticalDistanceOuter)) / 2;
    if (row % 2 == 0) {
        xPos = startPositionX + col * horizontalDistanceOuter - setXPosition(row);
        yPos = startPositionY + row * verticalDistanceOuter;
    } else {
        xPos = startPositionX + hexRadius + col * horizontalDistanceOuter - setXPosition(row);
        yPos = startPositionY + row * verticalDistanceOuter;
    }

    outerHexxagon.setPosition(xPos, yPos);
    innerHexxagon.setPosition(xPos, yPos);
}

void Hexagon::setOwner(int player) {
    isOccupied = true;
    owner = player;
    innerHexxagon.setFillColor(sf::Color::White); //really działa tekstura tylko jezeli przed tym zrobić bialy --_-- ja z tym 3h. męczyłem się...
    switch (player) {
        case 1: innerHexxagon.setTexture(&player1Texture);
        break;
        case 2: innerHexxagon.setTexture(&player2Texture);
        break;
        case 0: innerHexxagon.setFillColor(sf::Color::Transparent);
        break;
    }
}

void Hexagon::draw(sf::RenderWindow &window) {
    window.draw(outerHexxagon);
    window.draw(innerHexxagon);
}

bool Hexagon::contains(sf::Vector2f point) const {
    return outerHexxagon.getGlobalBounds().contains(point);
}

void Hexagon::getNeighbors(int row, int col) {
    // install neighbors for every hexxagon
    // we have 2 types of neighbors
    std::vector<std::pair<int, int> > beforeRowThreeFirst = {
        {0, -1}, {0, 1}, {-1, -1}, {-1, 0}, {1, 0}, {1, 1}
    };

    std::vector<std::pair<int, int> > beforeRowThreeSecond = {
        {-2, -2}, {-2, -1}, {-2, 0}, {-1, 1}, {0, 2}, {1, 2}, {2, 2},
        {2, 1}, {2, 0}, {1, -1}, {-1, -2}, {0, -2}
    };

    std::vector<std::pair<int, int> > rowThreeFirst = {
        {-1, -1}, {-1, 0}, {0, 1}, {1, 1}, {1, 0}, {0, -1}
    };

    std::vector<std::pair<int, int> > rowThreeSecond = {
        {0, 2}, {-1, 1}, {-2, 0}, {-2, -1}, {-2, -2}, {-1, -2}, {0, -2},
        {1, -1}, {2, -1}, {2, 0}, {2, 1}, {1, 2}
    };


    std::vector<std::pair<int, int> > rowFourFirst = {
        {-1, -1}, {-1, 0}, {0, 1}, {1, 0}, {1, -1}, {0, -1}
    };

    std::vector<std::pair<int, int> > rowFourSecond = {
        {0, -2}, {-1, -2}, {-2, -2}, {-2, -1}, {-2, 0}, {-1, 1}, {0, 2},
        {1, 1}, {2, 0}, {2, -1}, {2, -2}, {1, -2}
    };

    std::vector<std::pair<int, int> > rowFiveFirst = {
        {-1, 0}, {-1, 1}, {0, 1}, {0, -1}, {1, -1}, {1, 0}
    };

    std::vector<std::pair<int, int> > rowFiveSecond = {
        {-2, 0}, {-2, 1}, {-1, 2}, {0, 2}, {1, 1}, {2, 0}, {2, -1},
        {2, -2}, {1, -2}, {0, -2}, {-1, -1}, {-2, -1}
    };

    std::vector<std::pair<int, int> > afterFiveRowFirst = {
        {-1, 0}, {-1, 1}, {0, 1}, {0, -1}, {1, -1}, {1, 0}
    };

    std::vector<std::pair<int, int> > afterFiveRowSecond = {
        {-2, 0}, {-2, 1}, {-2, 2}, {-1, 2}, {0, 2}, {1, 1},
        {2, 0}, {2, -1}, {2, -2}, {1, -2}, {0, -2}, {-1, -1}
    };

    switch (row) {
        case 0:
        case 1:
        case 2:
            firstNeighborsPos = installNeighbors(row, col, beforeRowThreeFirst);
            secondNeighborsPos = installNeighbors(row, col, beforeRowThreeSecond);
            break;
        case 3:
            firstNeighborsPos = installNeighbors(row, col, rowThreeFirst);
            secondNeighborsPos = installNeighbors(row, col, rowThreeSecond);
            break;
        case 4:
            firstNeighborsPos = installNeighbors(row, col, rowFourFirst);
            secondNeighborsPos = installNeighbors(row, col, rowFourSecond);
            break;
        case 5:
            firstNeighborsPos = installNeighbors(row, col, rowFiveFirst);
            secondNeighborsPos = installNeighbors(row, col, rowFiveSecond);
            break;
        default:
            firstNeighborsPos = installNeighbors(row, col, afterFiveRowFirst);
            secondNeighborsPos = installNeighbors(row, col, afterFiveRowSecond);
            break;
    }
}

void Hexagon::installUnavailableHexagon(sf::RenderWindow &window) {
    isAvailable = false;
    owner = -100500;
    outerHexxagon.setOutlineColor(sf::Color::Transparent);
    outerHexxagon.setFillColor(sf::Color::Transparent);
    innerHexxagon.setOutlineColor(sf::Color::Transparent);
    innerHexxagon.setFillColor(sf::Color::Transparent);
}

int Hexagon::getOwner() const {
    return owner;
}

std::vector<std::pair<int, int> > Hexagon::getFirstNeighborsPos() const {
    return firstNeighborsPos;
}

std::vector<std::pair<int, int> > Hexagon::getSecondNeighborsPos() const {
    return secondNeighborsPos;
}

void Hexagon::setOutlineColor(sf::Color color) {
    innerHexxagon.setOutlineColor(color);
}

bool Hexagon::getIsAvailable() const {
    return isAvailable;
}

bool Hexagon::getIsOccupied() const {
    return isOccupied;
}

std::pair<int, int> Hexagon::getPosition() {
    return position;
}