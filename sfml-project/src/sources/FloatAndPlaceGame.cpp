#include "FloatAndPlaceGame.h"
#include <iostream>
#include <cmath>

FloatAndPlaceGame::FloatAndPlaceGame()
    : window(sf::VideoMode(800, 600), "Float & Place Game"),
      state(FOG_MENU),
      object(30.f),
      target(sf::Vector2f(100, 30)),
      velocity(0.f, 0.f),
      objectSelected(false)
{
    object.setFillColor(sf::Color::Cyan);
    object.setPosition(400, 500);

    target.setFillColor(sf::Color::Green);
    target.setPosition(350, 100);

    font.loadFromFile("assets/fonts/DejaVuSans.ttf");
}

void FloatAndPlaceGame::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void FloatAndPlaceGame::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (state == FOG_MENU && event.type == sf::Event::MouseButtonPressed) {
            if (object.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                state = FOG_PLAYING;
                objectSelected = true;
            }
        }
    }
}

void FloatAndPlaceGame::update() {
    if (state == FOG_PLAYING && objectSelected) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            velocity.x -= 0.5f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            velocity.x += 0.5f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            velocity.y -= 0.5f;

        velocity.y += 0.2f; // Gravity

        object.move(velocity);

        velocity.x *= 0.98f;
        velocity.y *= 0.98f;

        if (object.getPosition().y > 570) {
            state = FOG_GAME_OVER;
        }

        if (object.getGlobalBounds().intersects(target.getGlobalBounds()) &&
            std::abs(velocity.x) < 1.f && std::abs(velocity.y) < 1.f) {
            state = FOG_SUCCESS;
        }
    }
}

void FloatAndPlaceGame::render() {
    window.clear(sf::Color(30, 30, 60));
    window.draw(target);
    window.draw(object);

    sf::Text message;
    message.setFont(font);
    message.setCharacterSize(32);
    message.setFillColor(sf::Color::White);

    if (state == FOG_MENU) {
        message.setString("Click the object to start!");
        message.setPosition(220, 250);
        window.draw(message);
    } else if (state == FOG_GAME_OVER) {
        message.setString("Object broke! Game Over.");
        message.setPosition(200, 250);
        window.draw(message);
    } else if (state == FOG_SUCCESS) {
        message.setString("Success! You placed the object.");
        message.setPosition(170, 250);
        window.draw(message);
    }

    window.display();
}