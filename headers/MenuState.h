#ifndef MENU_STATE_H
#define MENU_STATE_H
#include "GameState.h"
#include "Global.h"
#include <raylib.h>
#include <iostream>
#include <vector>
using namespace std;

class MenuState : public GameState {
private:
    vector<Button> buttons;
    
public:
    void    handleInput(Game& game) override;
    void    init(Game& game ) override;
    void    update(Game& game) override;
    void    render(Game& game) override;
};
#endif