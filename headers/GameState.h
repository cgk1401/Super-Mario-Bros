#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <vector>
#include "Button.h"

class Game;

struct ButtonLayoutConfig {
    int amount_button;

    float MARGIN_ON;
    float MENU_BUTTON_HEIGHT;

    float BUTTON_MARGIN_X;
    float FIRST_POSITION_Y_BUTTON;
    float BUTTON_SPACING;

    float BUTTON_HEIGHT;
    float BUTTON_WIDTH;

    int FONT_SIZE;
    ButtonLayoutConfig(int amount_button, int fontSize = 30);
};

std::vector <Button*> CreateButtons(const char* buttonLabels[], const ButtonLayoutConfig& other);

//Lớp cha ảo => quản lí trạng thái của game: PlayState, PauseState,..
//State Pattern
class GameState{
public:
    bool shouldExit = false;
    virtual void handleInput() = 0;
    virtual void update(float deltatime) = 0;
    virtual void render() = 0;
    virtual bool allowUpdateBelow() { return true; }
    virtual ~GameState() = default;
};

#endif
