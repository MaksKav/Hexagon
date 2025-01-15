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

    void setPosition(sf::RenderWindow &window, float x, float y, const std::string &label); // Установка позиции кнопки
    void setText(sf::RenderWindow &window, float x, float y, const std::string &label); // Изменение текста кнопки
    virtual void draw(sf::RenderWindow &window); // Рисование кнопки
  //  bool isMouseOver(const sf::RenderWindow &window) const; // Проверка наведения мыши на кнопку
    std::string getText() const;

    // Метод для получения границ кнопки
    sf::FloatRect getGlobalBounds() const {
        return shape.getGlobalBounds();
    }

    // Проверка, находится ли курсор мыши внутри кнопки
    bool isMouseOver(sf::RenderWindow& window) const {
        // Получаем позицию мыши в мировых координатах
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)); // Проверяем, попадает ли позиция мыши в границы кнопки
    }

    // Проверка клика по кнопке
    bool isClicked(sf::RenderWindow& window, sf::Mouse::Button button) const {
        return isMouseOver(window) && sf::Mouse::isButtonPressed(button);
    }

    sf::RectangleShape &getShape();
    sf::Vector2f getGlobalPosition() const;

    void useActiveColor();
    void useInactiveColor();

    bool getClickedFlag() const;
    void setClickedFlag(bool clickedFlag);

};

#endif