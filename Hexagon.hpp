#ifndef HEXXAGON_HPP
#define HEXXAGON_HPP

#include <SFML/Graphics.hpp>

class Hexagon {
private:
    sf::CircleShape outerHexxagon;
    sf::CircleShape innerHexxagon;
    float xPos;
    float yPos;
    sf::Color defaultOutlineColor  ;
    sf::Color activeOutlineColor;
    bool isAvailable = true;
    bool isOccupied = false;
    int owner = 0;
    sf::Texture player1Texture;
    sf::Texture player2Texture;
    sf::Texture playerComputerTexture;
    std::vector<std::pair<int,int>> firstNeighborsPos;
    std::vector<std::pair<int,int>> secondNeighborsPos;
    int row;
    int col;

    void setOuterAndInnerHexxagonPositions(sf::RenderWindow& window , int row , int col);

    std::vector<std::pair<int,int>> installNeighbors(int row , int col , const std::vector<std::pair<int,int>>& vec);

    void getNeighbors(int row , int col);
public:
    Hexagon(sf::RenderWindow& window , int row , int col);
    Hexagon() {
        // Инициализация по умолчанию
    }
    void setOwner(int player);
    void draw(sf::RenderWindow& window);
    bool contains(sf::Vector2f point) const;
    int getOwner() const;
    std::vector<std::pair<int,int>> getFirstNeighborsPos() const;
    std::vector<std::pair<int,int>> getSecondNeighborsPos() const;

    void installUnavailableHexagon(sf::RenderWindow &window);
    static const float hexRadius;

    void setOutlineColor(sf::Color color);
    bool getIsAvailable() const;
    bool getIsOccupied() const;
};

#endif // HEXXAGON_HPP
