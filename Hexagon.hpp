#ifndef HEXXAGON_HPP
#define HEXXAGON_HPP

#include <SFML/Graphics.hpp>

class Hexagon {
private:
    sf::CircleShape outerHexxagon;
    sf::CircleShape innerHexxagon;
    float xPos;
    float yPos;
    sf::Color defaultOutline;
    bool isAvailable = true;
    bool isOccupied = false;
    int owner = 0;
    sf::Texture texture;
    std::vector<std::pair<int,int>> firstNeighborsPos;
    std::vector<std::pair<int,int>> secondNeighborsPos;

    void setOuterAndInnerHexxagonPositions(sf::RenderWindow& window , int row , int col);
    std::vector<std::pair<int,int>> installNeighbors(int row , int col , const std::vector<std::pair<int,int>>& vec);
public:
    Hexagon(sf::RenderWindow& window , int row , int col);

    void setOwner(int player, const sf::Texture& playerTexture);
    void draw(sf::RenderWindow& window);
    bool contains(sf::Vector2f point) const;
    int getOwner() const;
    std::vector<std::pair<int,int>> getFirstNeighborsPos() const;
    std::vector<std::pair<int,int>> getSecondNeighborsPos() const;

    void installUnavailableHexagon(sf::RenderWindow &window);
    static const float hexRadius;
};

#endif // HEXXAGON_HPP
