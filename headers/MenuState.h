#ifndef MENU_STATE_H
#define MENU_STATE_H
#include "../headers/GameState.h"
#include "../headers/Global.h"
#include "../headers/Button.h"
#include "../headers/Textbox.h"
#include "OptionState.h"
using namespace std;

class MenuState : public GameState {
private:
    Button* backButton;
    vector<Button*> buttons;
    vector<Button*> setting_buttons;
    Font font;
    Texture2D background;
    Texture2D mario_character;
    Texture2D luigi_character;
    int selectedButton = 0;
public:
    MenuState();
    ~MenuState();
    TextBox textbox;
    void    update(float deltatime) override;
    void    render() override;
};
#endif