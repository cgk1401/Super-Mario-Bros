#ifndef PLAY_STATE_H
#define PLAY_STATE_H
#include "GameState.h"
#include "GUI.h"
#include <raylib.h>
#include "PauseState.h"

class PlayState : public GameState{
public:
    bool isPlaying;
    void    handleInput(Game& game) override;
    void    init(Game& game ) override;
    void    update(Game& game) override;
    void    render(Game& game) override;
private:
    GUI gui;
    PauseState pause_button;
};

#endif