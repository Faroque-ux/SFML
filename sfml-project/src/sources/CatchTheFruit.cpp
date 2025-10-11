#include "CatchTheFruit.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

// Button implementation
Button::Button(float x, float y, float width, float height, const std::string& buttonText, sf::Font& buttonFont)
    : font(&buttonFont)
{
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(70, 70, 70));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);
    
    text.setFont(*font);
    text.setString(buttonText);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    
    // Center text in button - properly account for text bounds
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, 
                   textBounds.top + textBounds.height / 2.0f);
    text.setPosition(x + width / 2.0f, y + height / 2.0f);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isClicked(sf::Vector2i mousePos) {
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::setText(const std::string& newText) {
    text.setString(newText);
    
    // Recalculate centering when text changes
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, 
                   textBounds.top + textBounds.height / 2.0f);
    
    sf::Vector2f buttonPos = shape.getPosition();
    sf::Vector2f buttonSize = shape.getSize();
    text.setPosition(buttonPos.x + buttonSize.x / 2.0f, 
                     buttonPos.y + buttonSize.y / 2.0f);
}

void Button::setColor(sf::Color color) {
    shape.setFillColor(color);
}

// CatchTheFruit implementation
CatchTheFruit::CatchTheFruit() 
    : window(sf::VideoMode(800, 600), "Catch the Fruit!"),
      gameState(MENU),
      basket(sf::Vector2f(100.f, 30.f)),
      startButton(300, 250, 200, 50, "START GAME", font),
      pauseButton(650, 10, 100, 40, "PAUSE", font),
      resumeButton(300, 300, 200, 50, "RESUME", font),
      restartButton(300, 370, 200, 50, "RESTART", font),
      catchSound(catchBuffer),
      missSound(missBuffer),
      score(0),
      lives(5)
{
    window.setFramerateLimit(60);
    
    // Initialize basket
    basket.setFillColor(sf::Color(100, 50, 250));
    basket.setPosition(350.f, 550.f);
    
    // Load resources
    if (!loadFont()) {
        throw std::runtime_error("Failed to load font");
    }
    
    // Re-initialize buttons after font is loaded to ensure proper text centering
    startButton = Button(300, 250, 200, 50, "START GAME", font);
    pauseButton = Button(650, 10, 100, 40, "PAUSE", font);
    resumeButton = Button(300, 300, 200, 50, "RESUME", font);
    restartButton = Button(300, 370, 200, 50, "RESTART", font);
    
    // Initialize text objects
    scoreText.setFont(font);
    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    
    livesText.setFont(font);
    livesText.setString("Lives: 5");
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10, 40);
    
    titleText.setFont(font);
    titleText.setString("Catch the Fruit!");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::Yellow);
    // Center the title text
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, 
                        titleBounds.top + titleBounds.height / 2.0f);
    titleText.setPosition(400, 150);
    
    pausedText.setFont(font);
    pausedText.setString("PAUSED");
    pausedText.setCharacterSize(48);
    pausedText.setFillColor(sf::Color::Yellow);
    // Center the paused text
    sf::FloatRect pausedBounds = pausedText.getLocalBounds();
    pausedText.setOrigin(pausedBounds.left + pausedBounds.width / 2.0f, 
                         pausedBounds.top + pausedBounds.height / 2.0f);
    pausedText.setPosition(400, 150);
    
    loadSounds();
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

CatchTheFruit::~CatchTheFruit() {
    // Destructor - SFML handles cleanup automatically
}

bool CatchTheFruit::loadFont() {
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        if (!font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf")) {
            std::cout << "Could not load system fonts" << std::endl;
            return false;
        }
    }
    return true;
}

void CatchTheFruit::loadSounds() {
    catchBuffer.loadFromFile("catch.wav");
    missBuffer.loadFromFile("miss.wav");
}

void CatchTheFruit::run() {
    while (window.isOpen()) {
        handleEvents();
        updateGame();
        render();
    }
}

void CatchTheFruit::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            handleMouseClick(mousePos);
        }
        
        if (event.type == sf::Event::KeyPressed) {
            handleKeyPress(event.key.code);
        }
    }
}

void CatchTheFruit::handleMouseClick(sf::Vector2i mousePos) {
    switch (gameState) {
        case MENU:
            if (startButton.isClicked(mousePos)) {
                gameState = PLAYING;
                resetGame();
            }
            break;
            
        case PLAYING:
            if (pauseButton.isClicked(mousePos)) {
                gameState = PAUSED;
            }
            break;
            
        case PAUSED:
            if (resumeButton.isClicked(mousePos)) {
                gameState = PLAYING;
            } else if (restartButton.isClicked(mousePos)) {
                gameState = PLAYING;
                resetGame();
            }
            break;
            
        case GAME_OVER:
            if (restartButton.isClicked(mousePos)) {
                gameState = PLAYING;
                resetGame();
            }
            break;
    }
}

void CatchTheFruit::handleKeyPress(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Space) {
        if (gameState == PLAYING) {
            gameState = PAUSED;
        } else if (gameState == PAUSED) {
            gameState = PLAYING;
        }
    }
    if (key == sf::Keyboard::Escape) {
        if (gameState == PLAYING || gameState == PAUSED) {
            gameState = MENU;
        }
    }
}

void CatchTheFruit::updateGame() {
    if (gameState == PLAYING) {
        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && basket.getPosition().x > 0)
            basket.move(-8.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && basket.getPosition().x < 700)
            basket.move(8.f, 0.f);

        spawnFruit();
        updateFruits();

        // Update text
        scoreText.setString("Score: " + std::to_string(score));
        livesText.setString("Lives: " + std::to_string(lives));

        // Check for game over
        if (lives <= 0) {
            gameState = GAME_OVER;
        }
    }
}

void CatchTheFruit::spawnFruit() {
    if (spawnClock.getElapsedTime().asSeconds() > 0.8f) {
        Fruit fruit;
        fruit.shape = sf::CircleShape(20.f);
        fruit.shape.setFillColor(sf::Color::Blue);
        fruit.shape.setPosition(std::rand() % 760 + 20, -20);
        fruit.speed = 1.f ;//+ std::rand() % 3;
        fruits.push_back(fruit);
        spawnClock.restart();
    }
}

void CatchTheFruit::updateFruits() {
    for (auto it = fruits.begin(); it != fruits.end();) {
        it->shape.move(0, it->speed);

        // Check collision with basket
        if (it->shape.getGlobalBounds().intersects(basket.getGlobalBounds())) {
            score += 10;
            if (catchBuffer.getSampleCount() > 0) catchSound.play();
            it = fruits.erase(it);
        }
        // Missed fruit
        else if (it->shape.getPosition().y > 600) {
            lives--;
            if (missBuffer.getSampleCount() > 0) missSound.play();
            it = fruits.erase(it);
        } else {
            ++it;
        }
    }
}

void CatchTheFruit::render() {
    window.clear(sf::Color(30, 30, 60));
    
    switch (gameState) {
        case MENU:
        {
            window.draw(titleText);
            startButton.draw(window);
            break;
        }
            
        case PLAYING:
        {
            window.draw(basket);
            for (auto& fruit : fruits)
                window.draw(fruit.shape);
            window.draw(scoreText);
            window.draw(livesText);
            pauseButton.draw(window);
            break;
        }
            
        case PAUSED:
        {
            // Draw game elements in background (darker)
            sf::RectangleShape overlay(sf::Vector2f(800, 600));
            overlay.setFillColor(sf::Color(0, 0, 0, 128));
            
            window.draw(basket);
            for (auto& fruit : fruits)
                window.draw(fruit.shape);
            window.draw(scoreText);
            window.draw(livesText);
            window.draw(overlay);
            
            window.draw(pausedText);
            resumeButton.draw(window);
            restartButton.draw(window);
            break;
        }
            
        case GAME_OVER:
        {
            sf::Text gameOverText("Game Over!", font, 48);
            gameOverText.setFillColor(sf::Color::Red);
            // Center the game over text
            sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
            gameOverText.setOrigin(gameOverBounds.left + gameOverBounds.width / 2.0f, 
                                   gameOverBounds.top + gameOverBounds.height / 2.0f);
            gameOverText.setPosition(400, 200);
            
            sf::Text finalScoreText("Final Score: " + std::to_string(score), font, 24);
            finalScoreText.setFillColor(sf::Color::White);
            // Center the final score text
            sf::FloatRect scoreBounds = finalScoreText.getLocalBounds();
            finalScoreText.setOrigin(scoreBounds.left + scoreBounds.width / 2.0f, 
                                     scoreBounds.top + scoreBounds.height / 2.0f);
            finalScoreText.setPosition(400, 250);
            
            window.draw(gameOverText);
            window.draw(finalScoreText);
            restartButton.draw(window);
            break;
        }
    }
    
    window.display();
}

void CatchTheFruit::resetGame() {
    score = 0;
    lives = 5;
    fruits.clear();
    basket.setPosition(350.f, 550.f);
    spawnClock.restart();
    gameClock.restart();
}