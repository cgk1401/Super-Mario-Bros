#pragma once
#include <raylib.h>
#include "Button.h"
#include <vector>
#include "Game.h"
using namespace std;

//Display Menu: Resume, Restart, Save, Menu
class PauseState {
private:
    vector<Button*> buttons;
public:
    PauseState();
    ~PauseState();
    bool resume_IsCLicked();
    bool save_IsCLicked();
    void    handleInput(Game& game) ;
    void    update(Game& game);
    void    render();
};