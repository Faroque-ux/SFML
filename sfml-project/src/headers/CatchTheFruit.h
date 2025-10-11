#ifndef CATCHTHEFRUIT_H
#define CATCHTHEFRUIT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

struct Fruit {
    sf::CircleShape shape;
    float speed;
};

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font* font;
    
public:
    Button(float x, float y, float width, float height, const std::string& buttonText, sf::Font& buttonFont);
    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2i mousePos);
    void setText(const std::string& newText);
    void setColor(sf::Color color);
};

enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class CatchTheFruit {
private:
    sf::RenderWindow window;
    GameState gameState;
    
    // Game objects
    sf::RectangleShape basket;
    sf::Font font;
    sf::Text scoreText, livesText, titleText, pausedText;
    
    // Buttons
    Button startButton, pauseButton, resumeButton, restartButton;
    
    // Audio
    sf::SoundBuffer catchBuffer, missBuffer;
    sf::Sound catchSound, missSound;
    
    // Game state
    int score;
    int lives;
    std::vector<Fruit> fruits;
    sf::Clock spawnClock;
    sf::Clock gameClock;
    
    // Private methods
    void handleEvents();
    void handleMouseClick(sf::Vector2i mousePos);
    void handleKeyPress(sf::Keyboard::Key key);
    void updateGame();
    void spawnFruit();
    void updateFruits();
    void render();
    void resetGame();
    bool loadFont();
    void loadSounds();

public:
    CatchTheFruit();
    ~CatchTheFruit();
    void run();
};

#endif // CATCHTHEFRUIT_H