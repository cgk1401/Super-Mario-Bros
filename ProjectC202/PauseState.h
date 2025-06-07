#pragma once
#include <raylib.h>
#include "Button.h"
#include <vector>
#include "Game.h"
using namespace std;

//Displau Menu: Resume, Restart, Save, Menu
class PauseState {
private:
    vector<Button> buttons;
public:
    void    handleInput(Game& game) ;
    void    init(Game& game );
    void    update(Game& game);
    void    render(Game& game);
};