#pragma once

class IGame {
public:
    virtual ~IGame() = default;
    virtual void run() = 0;
};

IGame* createGame(int choice);