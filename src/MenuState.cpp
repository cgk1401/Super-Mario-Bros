#include "../headers/MenuState.h"
#include "../headers/Game.h"
#include "../headers/PlayState.h"
#include "../headers/MapEditor.h"
#include "../headers/CharacterSelection.h"
#include "../headers/AudioSettingsMenu.h"
#include "../headers/LevelState.h"

MenuState::MenuState() {
    Singleton<SoundManager>::getInstance().playMusic(MusicType::MENU_, true);
    TraceLog(LOG_INFO, "Menu: Constructor");
    // Mario Mario : fontsize = 100;
    const int amount_button = 3;
    buttons.resize(amount_button);

    ButtonLayoutConfig cfg(amount_button);
    const char* buttonLabels[amount_button] = {"PLAY", "LEVEL DESIGN", "EXIT"};
    buttons = CreateButtons(buttonLabels, cfg);

    const int amount_setting_button = 3;
    const char* setting_buttonLabels[amount_setting_button] = { "CHARACTER", "LEVEL", "MAP EDITOR" };
    ButtonLayoutConfig _cfg(amount_setting_button);
    setting_buttons = CreateButtons(setting_buttonLabels, amount_setting_button);

    backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);
    option_button = new Button("../assets/GUI/option_button.png", 10, 10, 100, 100, "", WHITE);
    font       = LoadFont("../assets/font/knightwarrior.otf");
    background      = Singleton<TextureManager>::getInstance().load(TextureType::BACKGROUND_1);
    mario_character = LoadTexture("../assets/GUI/menu_mario.png");
    luigi_character = LoadTexture("../assets/GUI/menu_luigi.png");
    textbox = TextBox(0, 0, 200, 40, "", RED, GRAY, BLACK);

    for(int i = 0; i < 5; i++){
        starAnimation.frame.push_back({(float)i * 600, 0, 600, 600});
    }
    for(int i = 4; i >= 0; i--){
        starAnimation.frame.push_back({(float)i * 600, 0, 600, 600});
    }
    starAnimation.durationtime = 0.08f;
    starTexture = LoadTexture("../assets/GUI/star_sprite.png");
    
}

MenuState::~MenuState() {
    delete backButton;
    delete option_button;
    
    for (auto& button : buttons) {
        delete button;
    }
    
    for (auto& button : setting_buttons) {
        delete button;
    }

    UnloadTexture(mario_character);
    UnloadFont(font);
}


void MenuState::handleInput() {
    if (selectedButton == 0) {
        if (option_button->IsClicked()) {
            Singleton<Game>::getInstance().addState(new AudioSettingsMenu());
        }
        else if (buttons[0]->IsClicked()) {
            Singleton<Game>::getInstance().addState(new OptionState());
        }
        else if (buttons[1]->IsClicked()) {
            Singleton<Game>::getInstance().addState(new LevelState(true));
        }
        else if (buttons[2]->IsClicked()) {
            exit(0);
        }
    }
    else if (selectedButton == 1) {
        if (setting_buttons[0]->IsClicked()) //CHARACTER
            Singleton<Game>::getInstance().addState(new CharacterSelection);
        else if (setting_buttons[1]->IsClicked()) { //LEVEL
            Singleton<Game>::getInstance().addState(new LevelState(true));
        }
        else if (setting_buttons[2]->IsClicked()) {
            Singleton<Game>::getInstance().changeState(new MapEditor());
            shouldExit = true;

        }
        else if (backButton->IsClicked()) {
            selectedButton = 0;
        }
    }
}
void MenuState::update(float deltatime){
    Singleton<SoundManager>::getInstance().updateMusic();
    starAnimation.Update(deltatime);
    if (selectedButton == 0) {
        option_button->update(deltatime);
        for (auto& button : buttons) {
            button->update(deltatime);
        }
    }
    else if (selectedButton == 1) {
        for (auto& button : setting_buttons) button->update(deltatime);
        backButton->update(deltatime);
    }

    
}

void MenuState::render(){
    DrawTexturePro(background,
			{0,0, (float)background.width,(float) background.height},
			{0,0, screenWidth, screenHeight},
			 {0,0}, 0, WHITE);
    ///_____________________________OPTIONS_________________________________________
    if (selectedButton == 0){
        option_button->draw();
        for (auto& button : buttons) {
            button->draw();
        }
    }
    else if (selectedButton == 1){   
        for (auto& button : setting_buttons)
                button->draw();
            backButton->draw();
    }
    ///_________________________HEADER TITLE____________________________________________
    DrawTextEx(font, "MARIO MARIO", {screenWidth * 0.33f, screenHeight * 0.1f}, 100, 5, DARKBROWN);

    ///_________________________MARIO/LUIGI____________________________________________
    DrawTexturePro(selectedCharacter == CharacterType::Mario ? mario_character : luigi_character,
        { 0,0, 1024, 1536 },
        { screenWidth * 0.6f, screenHeight * 0.4f, screenHeight / (1.77f * 1.50f), screenHeight / 1.77f },
        { 0,0 }, 0,
        WHITE
    );
    Rectangle src = starAnimation.getcurrentframe();
    DrawTexturePro(starTexture,
                src,
                {screenWidth * 0.767f, screenHeight * 0.212f, 140, 140},
                {0,0},
                17, WHITE);
    //textbox.Draw();
    
}