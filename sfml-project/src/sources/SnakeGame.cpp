#include "SnakeGame.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

SnakeGame::SnakeGame()
    : window(sf::VideoMode(600, 600), "Snake Game"),
      state(SNAKE_MENU),
      score(0),
      direction(1)
{
    font.loadFromFile("assets/fonts/DejaVuSans.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setPosition(10, 10);
    scoreText.setString("Score: 0");
    reset();
}

void SnakeGame::reset() {
    score = 0;
    direction = 1;
    snake.clear();
    sf::RectangleShape head(sf::Vector2f(20, 20));
    head.setFillColor(sf::Color::Green);
    head.setPosition(300, 300);
    snake.push_back(head);
    spawnFood();
    clock.restart();
}

void SnakeGame::spawnFood() {
    int x = (std::rand() % 30) * 20;
    int y = (std::rand() % 30) * 20;
    food = sf::RectangleShape(sf::Vector2f(20, 20));
    food.setFillColor(sf::Color::Red);
    food.setPosition(x, y);
}

void SnakeGame::run() {
    while (window.isOpen()) {
        handleEvents();
        if (state == SNAKE_PLAYING && clock.getElapsedTime().asSeconds() > moveDelay) {
            update();
            clock.restart();
        }
        render();
    }
}

void SnakeGame::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (state == SNAKE_MENU && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            state = SNAKE_PLAYING;
            reset();
        }

        if (state == SNAKE_PLAYING && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up && direction != 2) direction = 0;
            if (event.key.code == sf::Keyboard::Right && direction != 3) direction = 1;
            if (event.key.code == sf::Keyboard::Down && direction != 0) direction = 2;
            if (event.key.code == sf::Keyboard::Left && direction != 1) direction = 3;
        }
    }
}

void SnakeGame::update() {
    // Move snake
    sf::Vector2f move(0, 0);
    if (direction == 0) move.y = -20;
    if (direction == 1) move.x = 20;
    if (direction == 2) move.y = 20;
    if (direction == 3) move.x = -20;

    sf::Vector2f prevPos = snake[0].getPosition();
    snake[0].move(move);

    // Move body
    for (size_t i = 1; i < snake.size(); ++i) {
        sf::Vector2f temp = snake[i].getPosition();
        snake[i].setPosition(prevPos);
        prevPos = temp;
    }

    // Check collision with food
    if (snake[0].getGlobalBounds().intersects(food.getGlobalBounds())) {
        score++;
        scoreText.setString("Score: " + std::to_string(score));
        sf::RectangleShape newPart(sf::Vector2f(20, 20));
        newPart.setFillColor(sf::Color::Green);
        newPart.setPosition(prevPos);
        snake.push_back(newPart);
        spawnFood();
    }

    // Check collision with self or wall
    sf::Vector2f headPos = snake[0].getPosition();
    if (headPos.x < 0 || headPos.x >= 600 || headPos.y < 0 || headPos.y >= 600) {
        state = SNAKE_GAME_OVER;
    }
    for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[0].getGlobalBounds().intersects(snake[i].getGlobalBounds())) {
            state = SNAKE_GAME_OVER;
        }
    }
}

void SnakeGame::render() {
    window.clear(sf::Color::Black);

    if (state == SNAKE_MENU) {
        sf::Text title("Snake Game", font, 36);
        title.setFillColor(sf::Color::Cyan);
        sf::FloatRect tb = title.getLocalBounds();
        title.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
        title.setPosition(300, 200);
        window.draw(title);

        sf::Text start("Click to Start", font, 28);
        start.setFillColor(sf::Color::White);
        sf::FloatRect sb = start.getLocalBounds();
        start.setOrigin(sb.left + sb.width / 2.f, sb.top + sb.height / 2.f);
        start.setPosition(300, 300);
        window.draw(start);
    }
    else if (state == SNAKE_PLAYING) {
        window.draw(food);
        for (auto& part : snake)
            window.draw(part);
        window.draw(scoreText);
    }
    else if (state == SNAKE_GAME_OVER) {
        sf::Text gameOver("Game Over!", font, 36);
        gameOver.setFillColor(sf::Color::Red);
        sf::FloatRect gb = gameOver.getLocalBounds();
        gameOver.setOrigin(gb.left + gb.width / 2.f, gb.top + gb.height / 2.f);
        gameOver.setPosition(300, 250);
        window.draw(gameOver);

        sf::Text restart("Click to Restart", font, 28);
        restart.setFillColor(sf::Color::White);
        sf::FloatRect rb = restart.getLocalBounds();
        restart.setOrigin(rb.left + rb.width / 2.f, rb.top + rb.height / 2.f);
        restart.setPosition(300, 320);
        window.draw(restart);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            state = SNAKE_MENU;
        }
    }

    window.display();
}