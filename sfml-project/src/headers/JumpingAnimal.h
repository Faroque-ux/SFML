#pragma once
#include <SFML/Graphics.hpp>
#include "GameFactory.h"
#include "MenuButton.h"

class MenuButton;

enum JumpingAnimalState { JA_MENU, JA_PLAYING, JA_GAME_OVER };

class JumpingAnimal : public IGame {
public:
    JumpingAnimal();
    void run() override;

private:
    JumpingAnimalState state;
    MenuButton* startButton;
    sf::RenderWindow window;
    sf::RectangleShape ground;
    sf::Font font;
    sf::Text scoreText;
    int score;
    bool isJumping;
    float velocityY;
    const float gravity = 0.5f;
    const float jumpStrength = -14.0f;
    int level = 1;
    float obstacleSpeed = 8.0f;
    sf::Clock clock;
    sf::Clock obstacleClock;
    sf::Texture animalTex;
    sf::Sprite player;
    sf::Texture obstacleTex;
    std::vector<sf::Texture> obstacleTextures;
    std::vector<std::string> obstacleTextureFiles;
    sf::Sprite obstacle;

    void handleEvents();
    void update();
    void render();
};