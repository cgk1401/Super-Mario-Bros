#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "GameState.h"
#include <vector>
using namespace std;

//Áp dụng Singleton Pattern
class Game{
private: 
    static Game* instance;
    vector<GameState*> stateStack;
    Game();
    ~Game();

public:
    static Game* getInstance();

    void run();
    void init();

    void replaceState(GameState* newState);
    void addState(GameState* newGameState);
    void pop();
    void clear();
    int getStateCount();
};

#endif