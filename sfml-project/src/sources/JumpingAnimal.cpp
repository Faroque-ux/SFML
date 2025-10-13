#include "JumpingAnimal.h"
#include <SFML/Graphics.hpp>
#include <iostream>

JumpingAnimal::JumpingAnimal()
    : window(sf::VideoMode(800, 400), "Jumping Animal"),
      ground(sf::Vector2f(800, 40)),
     // player(sf::Vector2f(40, 40)),

      //obstacle(sf::Vector2f(30, 50)),
      score(0),
      isJumping(false),
      velocityY(0.0f),
      state(JA_MENU)
{
    startButton = new MenuButton(300, 180, 200, 60, "Start", font);
    window.setFramerateLimit(40);

    ground.setFillColor(sf::Color(100, 250, 50));
    ground.setPosition(0, 360);

    animalTex.loadFromFile("assets/textures/frog_sitting.png");
    player.setTexture(animalTex);
  
    //player.setFillColor(sf::Color::Cyan);
    player.setPosition(100, 320);

    // List of obstacle texture files
    obstacleTextureFiles = {
        "assets/textures/mushroom.png",
        "assets/textures/rock.png",
        "assets/textures/log.png",
        "assets/textures/leaf.png",
        "assets/textures/fire.png"
    };

    for (const auto& file : obstacleTextureFiles) {
        sf::Texture texture;
        if (texture.loadFromFile(file)) {
            obstacleTextures.push_back(texture);
        }
    }

    obstacle.setTexture(obstacleTextures[0]);
    //obstacle.setFillColor(sf::Color::Red);
    obstacle.setPosition(800, 310);

    if (!font.loadFromFile("assets/fonts/DejaVuSans.ttf")) {
        std::cerr << "Font loading failed!" << std::endl;
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setPosition(10, 10);
    scoreText.setString("Score: 0");
}

void JumpingAnimal::run() {
    while (window.isOpen()) {
        handleEvents();
         if (state == JA_PLAYING)
            update();
        render();
    }
}

void JumpingAnimal::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (state == JA_MENU && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (startButton->isClicked(mousePos)) {
                state = JA_PLAYING;
            }
        }
    }
    if (state == JA_PLAYING && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
        isJumping = true;
        velocityY = jumpStrength;
    }
}

void JumpingAnimal::update() {
    // Jump logic
    if (isJumping) {
        player.move(0, velocityY);
        velocityY += gravity;
        if (player.getPosition().y >= 320) {
            player.setPosition(player.getPosition().x, 320);
            isJumping = false;
        }
    }

    // Move obstacle
    obstacle.move(-obstacleSpeed, 0.f); //speed
    if (obstacle.getPosition().x < -50) {
        obstacle.setPosition(800, 310);
        score++;
        // Pick a random texture for the obstacle
        if (!obstacleTextures.empty()) {
            int idx = std::rand() % obstacleTextures.size();
            obstacle.setTexture(obstacleTextures[idx]);
        }

        // Level up every 10 points
        if (score % 10 == 0) {
            level++;
            obstacleSpeed += 1.0f; // Increase speed
        }
    }

    // Collision
    if (player.getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
        sf::Text gameOver("Game Over!", font, 48);
        gameOver.setFillColor(sf::Color::Yellow);
        gameOver.setPosition(250, 150);
        window.clear();
        window.draw(gameOver);
        window.display();
        sf::sleep(sf::seconds(2));
        window.close();
    }

    // Update score
    scoreText.setString("Score: " + std::to_string(score) + "  Level: " + std::to_string(level));
}

void JumpingAnimal::render() {
    window.clear(sf::Color(135, 206, 235));
    window.draw(ground);
    window.draw(player);
    window.draw(obstacle);
    window.draw(scoreText);

    if (state == JA_MENU) {
        sf::Text title("Jumping Animal", font, 36);
        title.setFillColor(sf::Color::Magenta);
        sf::FloatRect tb = title.getLocalBounds();
        title.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
        title.setPosition(400, 100);
        window.draw(title);

        startButton->draw(window);
    }

    window.display();
}