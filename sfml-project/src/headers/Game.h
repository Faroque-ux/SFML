#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    ~Game();

    void init();
    void update();
    void render();
    void handleInput();

private:
    sf::RenderWindow window;
    sf::Event event;
    // Add other game state variables here
};

#endif // GAME_H