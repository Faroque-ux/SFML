#include <SFML/Graphics.hpp>
#include "headers/Game.h"
#include "headers/CatchTheFruit.h"
#include "headers/FloatAndPlaceGame.h"
#include <iostream>
#include "GameFactory.h"
#include "MenuButton.h"

int main() {
   sf::RenderWindow window(sf::VideoMode(800, 600), "Game Selector");
    sf::Font font;
if (!font.loadFromFile("assets/fonts/DejaVuSans.ttf")) {
    std::cerr << "Font loading failed!" << std::endl;
    return -1;
}

    MenuButton btn1(250, 200, 300, 60, "Catch The Fruit", font);
    MenuButton btn2(250, 300, 300, 60, "Float And Place", font);

    bool gameSelected = false;
    int selectedGame = 0;

    while (window.isOpen() && !gameSelected) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (btn1.isClicked(mousePos)) {
                    selectedGame = 1;
                    gameSelected = true;
                }
                if (btn2.isClicked(mousePos)) {
                    selectedGame = 2;
                    gameSelected = true;
                }
            }
        }

        window.clear(sf::Color(30, 30, 60));
        sf::Text title("Select a Game", font, 40);
        title.setFillColor(sf::Color::Cyan);
        sf::FloatRect tb = title.getLocalBounds();
        title.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
        title.setPosition(400, 100);
        window.draw(title);

        btn1.draw(window);
        btn2.draw(window);

        window.display();
    }

    if (selectedGame > 0) {
        IGame* game = createGame(selectedGame);
        if (game) {
            game->run();
            delete game;
        }
    }

    return 0;
}