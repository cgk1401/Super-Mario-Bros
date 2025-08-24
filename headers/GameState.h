#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <vector>
#include "Button.h"

class Game;
//State Pattern
class GameState{
public:
    bool shouldExit = false;
    virtual void handleInput() = 0;
    virtual void update(float deltatime) = 0;
    virtual void render() = 0;
    virtual bool allowUpdateBelow() { return true; }
    virtual ~GameState() = default;
};

#endif
