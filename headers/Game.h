#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "GameState.h"
#include <vector>
#include "Global.h"
using namespace std;

template <typename T>
class Singleton;
//Áp dụng Singleton Pattern
class Game{
    template <typename T>
    friend class Singleton;
private: 
    vector<GameState*> stateStack;
    Game();
    ~Game();

public:

    void run();
    void init();

    void replaceState(GameState* newState);
    void addState(GameState* newGameState);
    void pop();
    void clear();
    int getStateCount();
};

#endif