#include "Hexagon.hpp"

#include <cmath>

const float Hexagon::hexRadius = 70;

Hexagon::Hexagon(sf::RenderWindow &window, int row, int col) {
    outerHexxagon = sf::CircleShape(hexRadius, 6);
    outerHexxagon.setOutlineThickness(10);
    outerHexxagon.setOutlineColor(sf::Color(0, 0, 0));
    outerHexxagon.setFillColor(sf::Color(128, 60, 128));

    innerHexxagon = sf::CircleShape(hexRadius, 6);
    innerHexxagon.setOutlineThickness(5);
    innerHexxagon.setOutlineColor(sf::Color(128, 0, 128));
    innerHexxagon.setFillColor(sf::Color::Transparent);

    // install neighbors for every hexxagon
    // we have 2 types of neighbors
    std::vector<std::pair<int, int> > beforeRowSixFirst = {
        {0, -1}, {0, 1}, {-1, -1}, {-1, 0}, {1, 0}, {1, 1}
    };
    std::vector<std::pair<int, int> > afterFiveRowFirst = {
        {0, -1}, {0, 1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}
    };
    firstNeighborsPos = row <= 5
                            ? installNeighbors(row, col, beforeRowSixFirst)
                            : installNeighbors(row, col, afterFiveRowFirst);


    std::vector<std::pair<int, int> > beforeRowSixSecond = {
        {2, 0}, {2, 1}, {2, 2}, {1, 2}, {0, 2},
        {-1, 1}, {-2, 0}, {-2, -1}, {-2, -2}, {-1, -2}, {0, -2}, {1, -1}
    };
    std::vector<std::pair<int, int> > afterFiveRowSecond = {
        {-2, 0}, {-1, -1}, {0, -2}, {1, -2}, {2, -2}, {2, -1},
        {2, 0}, {1, 1}, {0, 2}, {-1, 2}, {-2, 2}, {-2, 1}
    };
    secondNeighborsPos = row <= 5
                             ? installNeighbors(row, col, beforeRowSixSecond)
                             : installNeighbors(row, col, afterFiveRowSecond);


    setOuterAndInnerHexxagonPositions(window , row, col);
}


// std::vector<std::pair<int, int>> Hexagon::installNeighbors(int row, int col, const std::vector<std::pair<int, int>>& vec) {
//     std::vector<std::pair<int, int>> v;
//     for (const std::pair<int, int>& p: vec) {  // Исправлено: используем const для избежания копирования
//         auto newRow = row + p.first;
//         auto newCol = col + p.second;
//         if (newRow >= 0 && newCol >= 0 &&
//              ((row <= 5 && (newCol - newRow <= 4)) ||
//              (row >= 5 && (newCol - newRow >= -4 && newCol - newRow <= 2))
//              )) {
//             std::pair<int, int> newPair = {newRow, newCol};
//             v.push_back(newPair);
//                                                }
//     }
//     return v;
// }

std::vector<std::pair<int, int>> Hexagon::installNeighbors(int row, int col,const std::vector<std::pair<int, int>>& vec) {
    std::vector<std::pair<int, int>> v;
    for (const auto &p : vec) {
        int newRow = row + p.first;
        int newCol = col + p.second;
        if (newRow >= 0 && newCol >= 0 && (
                (row <= 5 && (newCol - newRow <= 4)) ||
                (row >= 5 && (newCol - newRow >= -4 && newCol - newRow <= 2))
            )) {
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


void Hexagon::setOwner(int player, const sf::Texture &playerTexture) {
    isOccupied = true;
    owner = player;
    texture = playerTexture;
    innerHexxagon.setFillColor(sf::Color::White);
    innerHexxagon.setTexture(&texture);
}

void Hexagon::draw(sf::RenderWindow &window) {
    window.draw(outerHexxagon);
    window.draw(innerHexxagon);
}

void Hexagon::installUnavailableHexagon(sf::RenderWindow &window) {
    isAvailable = false;
    isOccupied = true;
    outerHexxagon.setOutlineColor(sf::Color::Transparent);
    outerHexxagon.setFillColor(sf::Color::Transparent);
    innerHexxagon.setOutlineColor(sf::Color::Transparent);
    innerHexxagon.setFillColor(sf::Color::Transparent);
}


bool Hexagon::contains(sf::Vector2f point) const {
    return outerHexxagon.getGlobalBounds().contains(point);
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
