#include "../headers/MenuState.h"
#include "../headers/Game.h"
#include "../headers/PlayState.h"
#include "../headers/MapEditor.h"
#include "../headers/CharacterSelection.h"
#include "../headers/LevelState.h"

MenuState::MenuState() {
    TraceLog(LOG_INFO, "Menu: Constructor");
    // Mario Mario : fontsize = 100;
    const int amount_button = 3;
    buttons.resize(amount_button);

    ButtonLayoutConfig cfg(amount_button);
    const char* buttonLabels[amount_button] = {"PLAY", "SETTINGS", "EXIT"};
    
    buttons = CreateButtons(buttonLabels, cfg);


    const int amount_setting_button = 3;
    const char* setting_buttonLabels[amount_setting_button] = { "CHARACTER", "LEVEL", "MAP EDITOR"};

    ButtonLayoutConfig _cfg(amount_setting_button);
    setting_buttons = CreateButtons(setting_buttonLabels, amount_setting_button);

    backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);

    font       = LoadFont("../assets/font/knightwarrior.otf");

    background      = resizedImage("../assets/GUI/Menu Background.png", screenWidth, screenHeight);
    mario_character = LoadTexture("../assets/GUI/menu_mario.png");
    luigi_character = LoadTexture("../assets/GUI/menu_luigi.png");

    textbox = TextBox(0, 0, 200, 40, "", RED, GRAY, BLACK);
}

MenuState::~MenuState() {
    delete backButton;

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
    //textbox.update();
    if (selectedButton == 0) {
        for (auto& button : buttons) {
            button->update(deltatime);
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
        for (auto& button : setting_buttons) button->update(deltatime);
        backButton->update(deltatime);

        if (setting_buttons[0]->IsClicked()) //CHARACTER
            Singleton<Game>::getInstance().addState(new CharacterSelection);
        else if (setting_buttons[1]->IsClicked()) { //LEVEL
			Singleton<Game>::getInstance().addState(new LevelState);
        }
        else if (setting_buttons[2]->IsClicked()) {
            Singleton<Game>::getInstance().changeState(new MapEditor());
        }
        else if (backButton->IsClicked()) {
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
        {   for (auto& button : setting_buttons)
                button->draw();
            backButton->draw();
        }
    //HEADER TITLE
    DrawTextEx(font, "MARIO MARIO", {screenWidth * 0.33f, screenHeight * 0.1f}, 100, 5, DARKBROWN);
   
    
    DrawTexturePro(selectedCharacter == CharacterType::Mario ? mario_character : luigi_character,
        { 0,0, 1024, 1536 },
        { screenWidth * 0.6f, screenHeight * 0.4f, 300, 450 },
        { 0,0 }, 0,
        WHITE
    );
    //textbox.Draw();
    
}