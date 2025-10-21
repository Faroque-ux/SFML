#include "GameFactory.h"
#include "CatchTheFruit.h"
#include "FloatAndPlaceGame.h"
#include "JumpingAnimal.h"
#include "SnakeGame.h"

IGame* createGame(int choice) {
    if (choice == 1) return new CatchTheFruit();
    else if (choice == 2) return new FloatAndPlaceGame();
    else if (choice == 3) return new JumpingAnimal();
    else if (choice == 4) return new SnakeGame();
    else return nullptr;
}