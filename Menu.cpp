#include "Menu.hpp"

Menu::Menu( sf::RenderWindow& window) : menuWidth(window.getSize().x*0.8f), menuHeight(window.getSize().y*0.8f) {
    loadResources();
    initMenuButtons(window);
}

void Menu::loadResources() {
    if (!nameFont.loadFromFile("C:\\Users\\Maks\\CLionProjects\\Hexxagon\\resources\\fonts\\Jersey15-Regular.ttf")) {
        throw std::runtime_error("Can't load the font");
    }

    titleText.setFont(nameFont);
    titleText.setCharacterSize(250);
    titleText.setString("H E X X A G O N");
    titleText.setFillColor(sf::Color(255,215,0)); // gold color
}

void Menu::initMenuButtons(sf::RenderWindow& window) {
    auto buttonWidth = 700.f;
    auto buttonHeight = 70.f;
    sf::Color whiteWithAlpha = sf::Color(255,255,255,90);
    sf::Color black = sf::Color::Black;

    auto playButtonWidth = 700.f;
    Button playButton(playButtonWidth , buttonHeight ,"START GAME" , nameFont , whiteWithAlpha , black, 5.f);
    playButton.setPosition( window ,(window.getSize().x - playButtonWidth) / 2 , menuHeight, playButton.getText());
    addButton(playButton);

    auto playButtonGlobalPosition = playButton.getGlobalPosition();
    Button pvpButton(buttonWidth , buttonHeight , "PLAYER vs. PLAYER" , nameFont , whiteWithAlpha , black, 5.f);
    pvpButton.setPosition(window , playButtonGlobalPosition.x , playButtonGlobalPosition.y - 150 , pvpButton.getText());
    addButton(pvpButton);

    auto pvpButtonGlobalPosition = pvpButton.getGlobalPosition();
    Button pvcButton(buttonWidth , buttonHeight , "PLAYER vs. COMPUTER" , nameFont , whiteWithAlpha , black, 5.f);
    pvcButton.setPosition(window , playButtonGlobalPosition.x , pvpButtonGlobalPosition.y - 100 , pvpButton.getText());
    addButton(pvcButton);
}


void Menu::addButton(const Button& button) {
    buttons.push_back(button);
}

void Menu::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        for (auto& button : buttons) {
            /*if (button.isMouseOver(mousePos)) {
                // Действие при нажатии на кнопку (вызывайте соответствующую функцию)
                std::cout << "Button clicked!" << std::endl;
            }*/
        }
    }
}

void Menu::draw(sf::RenderWindow& window) {
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;

    float menuWidth = windowWidth * 0.8f;
    float menuHeight = windowHeight * 0.8f;

    background.setSize(sf::Vector2f(menuWidth, menuHeight));
    background.setFillColor(sf::Color(50,0,80,70));
    background.setPosition(sf::Vector2f((windowWidth - menuWidth) / 2 , (windowHeight - menuHeight) / 2));

    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setPosition((windowWidth - textRect.width) / 2 , -10);

    window.draw(background);
    window.draw(titleText);

    for (Button& button : buttons) {
        button.draw(window);
    }
}



