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
    Button* option_button;
    vector<Button*> buttons;
    vector<Button*> setting_buttons;
    Font font;
    Texture2D background;
    Texture2D mario_character;
    Texture2D luigi_character;
    int selectedButton = 0;

    Animation starAnimation;
    Texture2D starTexture;

public:
    MenuState();
    ~MenuState();
    TextBox textbox;


    void handleInput() override;
    void    update(float deltatime) override;
    void    render() override;
};
#endif