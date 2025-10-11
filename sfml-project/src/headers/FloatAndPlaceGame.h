#ifndef FLOATANDPLACEGAME_H
#define FLOATANDPLACEGAME_H

#include <SFML/Graphics.hpp>
#include "GameFactory.h"
enum FlyingObjectGameState { FOG_MENU, FOG_LAUNCH, FOG_PLAYING, FOG_GAME_OVER, FOG_SUCCESS };

class FloatAndPlaceGame : public IGame {
public:
    FloatAndPlaceGame();
    void run() override;

private:
    sf::RenderWindow window;
    sf::View view;
    FlyingObjectGameState state;
    sf::CircleShape object;
    sf::RectangleShape target;
    sf::Vector2f velocity;
    bool objectSelected;
    sf::Font font;
    float scrollSpeed = 2.0f; // pixels per frame
    int launchTimer;

    void handleEvents();
    void update();
    void render();
};

#endif // FLOATANDPLACEGAME_H