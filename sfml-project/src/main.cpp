#include <SFML/Graphics.hpp>
#include "headers/Game.h"
#include "headers/CatchTheFruit.h"
#include <iostream>

int main() {
    try {
        CatchTheFruit game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}