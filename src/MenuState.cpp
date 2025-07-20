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

    ButtonLayoutConfig cfg(amount_button);
    const char* buttonLabels[amount_button] = {"PLAY", "SETTINGS", "CHARACTER", "LEVEL", "EXIT"};
    
    buttons = CreateButtons(buttonLabels, cfg);
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