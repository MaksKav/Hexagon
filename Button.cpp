#include "Button.hpp"
Button::Button(float width, float height, const std::string &label, const sf::Font &font,
               sf::Color fillColor, sf::Color outlineColor, float outlineThickness )
    : defaultColor(fillColor), defaultOutlineColor(outlineColor), outlineThickness(outlineThickness) {
    setClickedFlag(false);
    activeColor = sf::Color(defaultColor.r, defaultColor.g, defaultColor.b, 255);
    activeOutlineColor = sf::Color(255, 215, 0) , clickedFlag = false; // gold color

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


void Button::draw(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(text);
}


void Button::useActiveColor() {
    shape.setFillColor(activeColor);
    shape.setOutlineColor(activeOutlineColor);
}

void Button::useInactiveColor() {
    shape.setFillColor(defaultColor);
    shape.setOutlineColor(defaultOutlineColor);
}

std::string Button::getText() const {
    return text.getString();
}

sf::RectangleShape &Button::getShape() {
    return shape;
}

void Button::setPosition(sf::RenderWindow &window, float x, float y, const std::string &label) {
    shape.setPosition(x, y);
    setTextPos(window, x, y);
}

void Button::setTextPos(sf::RenderWindow &window, float shapeX, float shapeY) {
    sf::FloatRect shapeRect = shape.getGlobalBounds();
    sf::FloatRect textRect = text.getLocalBounds();

    text.setPosition(shapeX + (shapeRect.width - textRect.width) / 2,
                     shapeY - (shapeRect.height - textRect.height) / 5);
}

void Button::setText(const std::string &t) {
    text.setString(t);
}

void Button::setTextColor(sf::Color color) {
    text.setFillColor(color);
}

sf::Vector2f Button::getGlobalPosition() const {
    return shape.getPosition();
}

bool Button::getClickedFlag() const {
    return clickedFlag;
};

void Button::setClickedFlag(bool flag) {
    clickedFlag = flag;
};




