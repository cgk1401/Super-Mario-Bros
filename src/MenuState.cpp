#include "../headers/MenuState.h"
#include "../headers/Game.h"
#include "../headers/PlayState.h"
#include "../headers/MapEditor.h"
#include "../headers/CharacterSelection.h"

MenuState::MenuState() {
    TraceLog(LOG_INFO, "Menu: Constructor");
    // Mario Mario : fontsize = 100;
    const int amount_button = 5;
    buttons.resize(amount_button);

    const float MARGIN_ON = screenHeight * 0.1f;
    const float MENU_BUTTON_HEIGHT = screenHeight - 2 * MARGIN_ON - 100.0f - 40;

    const float BUTTON_MARGIN_X = screenWidth * 0.35f;
    const float FIRST_POSITION_Y_BUTTON = MARGIN_ON + 100.0f;
    const float BUTTON_SPACING = 15.0f;

    const float BUTTON_HEIGHT = float(MENU_BUTTON_HEIGHT - BUTTON_SPACING * 2 ) / amount_button;
    const float BUTTON_WIDTH = screenWidth / 3;

    const char* buttonLabels[amount_button] = {"PLAY", "SETTINGS", "CHARACTER", "LEVEL", "EXIT"};
    for (int i = 0; i < amount_button; i++) {
        buttons[i] = new Button("../assets/GUI/Button.png", BUTTON_MARGIN_X, FIRST_POSITION_Y_BUTTON + i * (BUTTON_HEIGHT + BUTTON_SPACING), BUTTON_WIDTH, BUTTON_HEIGHT, buttonLabels[i], WHITE, 30);
    }
    /*buttons[0] = new Button("../assets/GUI/Button.png", screenWidth * 0.35f, screenHeight * 0.25, screenWidth / 3, screenHeight / 5, "PLAY", WHITE, 40);
    buttons[1] = new Button("../assets/GUI/Button.png",screenWidth * 0.35f, screenHeight *0.25 + screenHeight / 5 + 5, screenWidth / 3, screenHeight / 5, "SETTINGS", WHITE, 40);
    buttons[2] = new Button("../assets/GUI/Button.png", screenWidth * 0.35f, screenHeight * 0.25 + 2 * screenHeight / 5 + 10, screenWidth / 3, screenHeight / 5, "EXIT", WHITE, 40);*/


    font       = LoadFont("../assets/font/knightwarrior.otf");

    background      = resizedImage("../assets/GUI/Menu Background.png", screenWidth, screenHeight);
    mario_character = resizedImage("../assets/GUI/Menu Mario.png", 400, 400);
}

MenuState::~MenuState() {
    for (auto& button : buttons) {
        delete button;
    }

    UnloadTexture(background);
    UnloadTexture(mario_character);
    UnloadFont(font);
}

void MenuState::update(float deltatime){
    for(auto& button: buttons){
        button->update();
    }

    if(buttons[0]->IsClicked()){
        Singleton<Game>::getInstance().clear();
        Singleton<Game>::getInstance().addState(new PlayState());
    }
    else if (buttons[1]->IsClicked()) {
        Singleton<Game>::getInstance().clear();
        Singleton<Game>::getInstance().addState(new MapEditor("../assets/Map/tileset_gutter64x64.png"));
    }
    else if (buttons[2]->IsClicked()) {
        Singleton<Game>::getInstance().replaceState(new CharacterSelection());
    }
    else if(buttons[4]->IsClicked()){
        exit(0);
    }
}

void MenuState::render(){
    DrawTexture(background, 0, 0, WHITE);
    
    for(auto& button: buttons){
        button->draw();
    } 
    //HEADER TITLE
    DrawTextEx(font, "MARIO MARIO", {screenWidth * 0.33f, screenHeight * 0.1f}, 100, 5, DARKBROWN);
   
    
    DrawTexture(mario_character, screenWidth * 0.6f, screenHeight * 0.4f, WHITE);
    
}