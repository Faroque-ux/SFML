#pragma once
#include <SFML/Graphics.hpp>
#include "GameFactory.h"

enum SnakeGameState { SNAKE_MENU, SNAKE_PLAYING, SNAKE_GAME_OVER };

class SnakeGame : public IGame {
public:
    SnakeGame();
    void run() override;

private:
    SnakeGameState state;
    sf::RenderWindow window;
    sf::Font font;
    sf::Text scoreText;
    int score;
    int direction; // 0=up, 1=right, 2=down, 3=left
    sf::Clock clock;
    float moveDelay = 0.12f;
    std::vector<sf::RectangleShape> snake;
    sf::RectangleShape food;
    //sf::CircleShape headShape;

    void handleEvents();
    void update();
    void render();
    void reset();
    void spawnFood();
};