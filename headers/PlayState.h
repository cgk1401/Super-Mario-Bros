#ifndef PLAY_STATE_H
#define PLAY_STATE_H
#include "GameState.h"
#include "GUI.h"
#include <raylib.h>
#include "PauseState.h"

class PlayState : public GameState{
public:
    PlayState();
    ~PlayState();
    void    handleInput(Game& game) override;
    void    update(Game& game) override;
    void    render() override;
private:
    bool isPlaying;
    GUI gui;
    PauseState pauseMenu;
};

#endif