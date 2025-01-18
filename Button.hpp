#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    bool clickedFlag;
    sf::Color defaultColor;
    sf::Color activeColor;
    sf::Color defaultOutlineColor;
    sf::Color activeOutlineColor;
    float outlineThickness;

public:
    Button(float width, float height, const std::string &label, const sf::Font &font,
           sf::Color fillColor, sf::Color outlineColor, float outlineThickness);

    void setPosition(sf::RenderWindow &window, float x, float y);
    virtual void draw(sf::RenderWindow &window);

    sf::FloatRect getGlobalBounds() const {
        return shape.getGlobalBounds();

    }

    bool isMouseOver(sf::RenderWindow& window) const {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    bool isClicked(sf::RenderWindow& window, sf::Mouse::Button button) const {
        return isMouseOver(window) && sf::Mouse::isButtonPressed(button);
    }

    sf::RectangleShape &getShape();
    sf::Vector2f getGlobalPosition() const;

    void useActiveColor();
    void useInactiveColor();

    bool getClickedFlag() const;
    void setClickedFlag(bool clickedFlag);

    void setTextPos(sf::RenderWindow &window, float x, float y);
    std::string getText() const;
    void setTextColor(sf::Color color);
    void setText(const std::string &t);
    void setTextSize(int size);

};

#endif