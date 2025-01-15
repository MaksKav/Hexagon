#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;

    sf::Color defaultColor;
    sf::Color activeColor;
    sf::Color defaultOutlineColor;
    sf::Color activeOutlineColor;
    float outlineThickness;

public:
    Button(float width, float height, const std::string &label, const sf::Font &font,
           sf::Color fillColor, sf::Color outlineColor, float outlineThickness);

    void setPosition(sf::RenderWindow &window, float x, float y, const std::string &label); // Установка позиции кнопки
    void setText(sf::RenderWindow &window, float x, float y, const std::string &label); // Изменение текста кнопки
    virtual void draw(sf::RenderWindow &window); // Рисование кнопки
    bool isMouseOver(const sf::RenderWindow &window) const; // Проверка наведения мыши на кнопку
    std::string getText() const;

    sf::RectangleShape &getShape();

    sf::Vector2f getGlobalPosition() const;

    void setActiveColor();

    void setInactiveColor();

};

#endif
