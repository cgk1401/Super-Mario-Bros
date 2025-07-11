#ifndef MENU_STATE_H
#define MENU_STATE_H
#include "../headers/GameState.h"
#include "../headers/Global.h"
#include "../headers/Button.h"
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
 
    void    update(float deltatime) override;
    void    render() override;
};
#endif