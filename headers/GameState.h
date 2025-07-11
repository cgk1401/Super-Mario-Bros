#ifndef GAME_STATE_H
#define GAME_STATE_H

class Game;

//Lớp cha ảo => quản lí trạng thái của game: PlayState, PauseState,..
//State Pattern
class GameState{
public:
    //virtual void handleInput() = 0;
    virtual void update(float deltatime) = 0;
    virtual void render() = 0;
    virtual bool allowUpdateBelow() { return true; }
    virtual ~GameState() = default;
};

#endif
