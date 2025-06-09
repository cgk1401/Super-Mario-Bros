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
    vector<Button*> buttons;
    Font font;
    Texture2D background;
    Texture2D mario_character;
public:
    MenuState();
    ~MenuState();
    void    handleInput(Game& game) override;
    void    update(Game& game) override;
    void    render() override;
};
#endif