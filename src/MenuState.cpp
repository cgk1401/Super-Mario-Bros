#include "../headers/MenuState.h"
#include "../headers/Game.h"
#include "../headers/PlayState.h"
#include "../headers/MapEditor.h"
#include "../headers/CharacterSelection.h"

MenuState::MenuState() {
    TraceLog(LOG_INFO, "Menu: Constructor");
    // Mario Mario : fontsize = 100;
    const int amount_button = 3;
    buttons.resize(amount_button);

    ButtonLayoutConfig cfg(amount_button);
    const char* buttonLabels[amount_button] = {"PLAY", "SETTINGS", "EXIT"};
    
    buttons = CreateButtons(buttonLabels, cfg);


    const int amount_setting_button = 4;
    const char* setting_buttonLabels[amount_setting_button] = { "CHARACTER", "LEVEL", "MAP EDITOR", "RETURN MENU"};

    ButtonLayoutConfig _cfg(amount_setting_button);
    setting_buttons = CreateButtons(setting_buttonLabels, amount_setting_button);

   

    font       = LoadFont("../assets/font/knightwarrior.otf");

    background      = resizedImage("../assets/GUI/Menu Background.png", screenWidth, screenHeight);
    mario_character = LoadTexture("../assets/GUI/menu_mario.png");
    luigi_character = LoadTexture("../assets/GUI/menu_luigi.png");
}

MenuState::~MenuState() {
    for (auto& button : buttons) {
        delete button;
    }
    
    for (auto& button : setting_buttons) {
        delete button;
    }


    UnloadTexture(background);
    UnloadTexture(mario_character);
    UnloadFont(font);
}

void MenuState::update(float deltatime){
    if (selectedButton == 0) {
        for (auto& button : buttons) {
            button->update();
        }

        if (buttons[0]->IsClicked()) {
            Singleton<Game>::getInstance().clear();
            Singleton<Game>::getInstance().addState(new PlayState());
        }
        else if (buttons[1]->IsClicked()) {
            selectedButton = 1; //setting_buttons
        }
        else if (buttons[2]->IsClicked()) {
            exit(0);
        }
    }
    else if (selectedButton == 1) {
        for (auto& button : setting_buttons) button->update();
        if (setting_buttons[0]->IsClicked()) //CHARACTER
            Singleton<Game>::getInstance().changeState(new CharacterSelection);
        else if (setting_buttons[1]->IsClicked()) { //LEVEL

        }
        else if (setting_buttons[2]->IsClicked()) {
            Singleton<Game>::getInstance().changeState(new MapEditor("../assets/Map/tileset_gutter64x64.png"));
        }
        else if (setting_buttons[3]->IsClicked()) {
            selectedButton = 0;
        }
    }

    
}

void MenuState::render(){
    DrawTexture(background, 0, 0, WHITE);
    if (selectedButton == 0)
        for (auto& button : buttons) {
            button->draw();
        }
    else if (selectedButton == 1)
        for (auto& button : setting_buttons)
            button->draw();
    //HEADER TITLE
    DrawTextEx(font, "MARIO MARIO", {screenWidth * 0.33f, screenHeight * 0.1f}, 100, 5, DARKBROWN);
   
    
    DrawTexturePro(selectedCharacter == CharacterType::Mario ? mario_character : luigi_character,
        { 0,0, 1024, 1536 },
        { screenWidth * 0.6f, screenHeight * 0.4f, 300, 450 },
        { 0,0 }, 0,
        WHITE
    );
}