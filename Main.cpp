#include "Game.hpp"
#include "HexagonBoard.hpp"

auto main() -> int {
    // Создаем окно
    auto window = sf::RenderWindow(sf::VideoMode(1800, 1400), "Hexagon");
    auto x = HexagonBoard(window);

    // Главный цикл приложения
    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Закрытие окна
            }
        }

        // Отрисовка
        window.clear();
        x.draw(window);
        window.display();
    }

    return 0;
}
