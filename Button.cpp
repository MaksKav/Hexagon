#include "Button.hpp"

Button::Button(float width, float height, const std::string &label, const sf::Font &font,
               sf::Color fillColor, sf::Color outlineColor, float outlineThickness)
    : defaultColor(fillColor), defaultOutlineColor(outlineColor), outlineThickness(outlineThickness) {
    activeColor = sf::Color(defaultColor.r, defaultColor.g, defaultColor.b, 255);
    activeOutlineColor = sf::Color(255, 215, 0); // gold color

    // Set a button form
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(defaultColor);
    shape.setOutlineColor(defaultOutlineColor);
    shape.setOutlineThickness(outlineThickness);

    // Set the text in button
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color::Black);
}

static std::vector<Button *> toggleableButtons;

void Button::setPosition(sf::RenderWindow &window, float x, float y, const std::string &label) {
    shape.setPosition(x, y);
    setText(window, x, y, label);
}

void Button::setText(sf::RenderWindow &window, float shapeX, float shapeY, const std::string &label) {
    sf::FloatRect shapeRect = shape.getGlobalBounds();
    sf::FloatRect textRect = text.getLocalBounds();

    text.setPosition(shapeX + (shapeRect.width - textRect.width) / 2,
                     shapeY - (shapeRect.height - textRect.height) / 5);
}


void Button::draw(sf::RenderWindow &window) {
    bool isMouseOverAny = isMouseOver(window);
    if (isMouseOverAny) {
        this->setActiveColor();
    } else {
        this->setInactiveColor();
    }

    window.draw(shape);
    window.draw(text);
}

bool Button::isMouseOver(const sf::RenderWindow &window) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window); // get a mouse coordinates in window
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::setActiveColor() {
    shape.setFillColor(activeColor);
    shape.setOutlineColor(activeOutlineColor);
}

void Button::setInactiveColor() {
    shape.setFillColor(defaultColor);
    shape.setOutlineColor(defaultOutlineColor);
}

std::string Button::getText() const {
    return text.getString();
}

sf::RectangleShape &Button::getShape() {
    return shape;
}

sf::Vector2f Button::getGlobalPosition() const {
    return shape.getPosition();
}
