#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "GameState.h"

//Áp dụng Singleton Pattern: chỉ 1 instance của class này suốt cả quá trình chạy game
class Game{
private: 
    static Game* instance;
    GameState* currentState;

    Game();
    ~Game();

public:
    static Game* getInstance();

    void run();
    void init();
    void changeState(GameState* newGameState);
};

#endif