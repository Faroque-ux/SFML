#include "GameFactory.h"
#include "CatchTheFruit.h"
#include "FloatAndPlaceGame.h"

IGame* createGame(int choice) {
    if (choice == 1) return new CatchTheFruit();
    else if (choice == 2) return new FloatAndPlaceGame();
    else return nullptr;
}