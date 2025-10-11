#include "FloatAndPlaceGame.h"
#include <iostream>
#include <cmath>

sf::Texture bgTexture;
sf::Sprite bgSprite;

FloatAndPlaceGame::FloatAndPlaceGame()
    : window(sf::VideoMode(800, 600), "Float & Place Game"),
      view(sf::FloatRect(0, 0, 800, 600)),
      state(FOG_MENU),
      object(30.f),
      target(sf::Vector2f(100, 30)),
      velocity(0.f, 0.f),
      objectSelected(false),
      launchTimer(0)
{
    object.setFillColor(sf::Color::Cyan);
    object.setPosition(400, 500);

    target.setFillColor(sf::Color::Green);
    target.setPosition(1200, 500);

    font.loadFromFile("assets/fonts/DejaVuSans.ttf");
    window.setView(view);

    // Load background texture
    bgTexture.loadFromFile("assets/textures/background.png");
    bgSprite.setTexture(bgTexture);
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
                state = FOG_LAUNCH;
                objectSelected = true;
                launchTimer = 0;
                velocity = sf::Vector2f(0.f, -6.f); // Initial upward velocity
            }
        }
    }
}

void FloatAndPlaceGame::update() {
     if (state == FOG_LAUNCH && objectSelected) {
        object.move(velocity);
        velocity.y += 0.05f; // gravity

        launchTimer++;
        if (launchTimer > 40) {
            state = FOG_PLAYING;
        }

        // Center the view on the object (horizontal only)
        view.setCenter(object.getPosition().x, view.getCenter().y);
        window.setView(view);

        if (object.getPosition().y > view.getCenter().y + 300) {
            state = FOG_GAME_OVER;
        }
    }
    else if (state == FOG_PLAYING && objectSelected) {
        // Keyboard controls for both axes (reduced acceleration)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            velocity.x -= 0.2f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            velocity.x += 0.2f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            velocity.y -= 0.2f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            velocity.y += 0.2f;

        // Gravity (reduced)
        velocity.y += 0.05f;

        // Move object
        object.move(velocity);

        // Friction (increased)
        velocity.x *= 0.95f;
        velocity.y *= 0.95f;

        // Scroll the view to the right
        view.setCenter(object.getPosition().x, view.getCenter().y);
        window.setView(view);

        // Check for falling
        if (object.getPosition().y > view.getCenter().y + 300) {
            state = FOG_GAME_OVER;
        }

        // Check for success
        if (object.getGlobalBounds().intersects(target.getGlobalBounds()) &&
            std::abs(velocity.x) < 1.f && std::abs(velocity.y) < 1.f) {
            state = FOG_SUCCESS;
        }
    }
}

void FloatAndPlaceGame::render() {
    window.clear(sf::Color(30, 30, 60));

    // Draw background tiles across a wide area
    sf::Vector2f viewPos = view.getCenter();
    float left = viewPos.x - view.getSize().x / 2;
    float right = viewPos.x + view.getSize().x / 2;
    for (float x = left - 800; x < right + 800; x += bgTexture.getSize().x) {
        bgSprite.setPosition(x, 0);
        window.draw(bgSprite);
    }


    window.draw(target);
    window.draw(object);

    sf::Text message;
    message.setFont(font);
    message.setCharacterSize(32);
    message.setFillColor(sf::Color::White);

    if (state == FOG_MENU) {
        message.setString("Click the object to start!");
        message.setPosition(view.getCenter().x - 180, view.getCenter().y - 50);
        window.draw(message);
    } else if (state == FOG_GAME_OVER) {
        message.setString("Object broke! Game Over.");
        message.setPosition(view.getCenter().x - 200, view.getCenter().y - 50);
        window.draw(message);
    } else if (state == FOG_SUCCESS) {
        message.setString("Success! You placed the object.");
        message.setPosition(view.getCenter().x - 230, view.getCenter().y - 50);
        window.draw(message);
    }

    window.display();
}