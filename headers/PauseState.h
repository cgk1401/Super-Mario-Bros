#pragma once
#include <raylib.h>
#include "Button.h"
#include <vector>
#include "Game.h"
#include "../headers/GameState.h"
using namespace std;

//Display Menu: Resume, Restart, Save, Menu
class PauseState : public GameState{
private:
    vector<Button*> buttons;
public:
    PauseState();
    ~PauseState();

    void    update(float deltatime);
    void    render();
    bool allowUpdateBelow() override { return false; }
};