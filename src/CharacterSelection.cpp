#include "../headers/CharacterSelection.h"
#include "../headers/PlayState.h"
#include "../headers/MenuState.h"

CharacterSelection::CharacterSelection() {
    const int amount_button = 2;
    buttons.resize(amount_button);

    ButtonLayoutConfig cfg(amount_button, 50);
    const char* buttonLabels[amount_button] = { "Mario", "Luigi"};
   
    buttons = CreateButtons(buttonLabels, cfg);
    font = LoadFont("../assets/font/knightwarrior.otf");

    backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);

    background = resizedImage("../assets/GUI/Menu Background.png", screenWidth, screenHeight);
    characters.resize(2);
    characters[0] = LoadTexture("../assets/GUI/menu_mario.png");
    characters[1] = LoadTexture("../assets/GUI/menu_luigi.png");
    selectCharacter = &characters[0];
}

CharacterSelection::~CharacterSelection() {
    for (auto& button : buttons) delete button;
    for (auto& character : characters) UnloadTexture(character);
    delete backButton;

    UnloadTexture(background);
    UnloadFont(font);
}

void CharacterSelection::update(float deltatime) {
    for (auto& button : buttons) {
        button->update(deltatime);
    }
    backButton->update(deltatime);

    if (buttons[0]->IsClicked()) {
        selectCharacter = &characters[0];
        selectedCharacter = CharacterType::Mario;
    }
    else if (buttons[1]->IsClicked()) {
        selectCharacter = &characters[1];
        selectedCharacter = CharacterType::Luigi;
        
    }
    else if (backButton->IsClicked()) {
        Singleton<Game>::getInstance().pop();
    }
    
}

void CharacterSelection::render() {
    DrawTexture(background, 0, 0, WHITE);
    backButton->draw();
    for (auto& button : buttons) {
        button->draw();
    }
    //HEADER TITLE
    DrawTextEx(font, "MARIO MARIO", { screenWidth * 0.33f, screenHeight * 0.1f }, 100, 5, DARKBROWN);
    DrawTexturePro(*selectCharacter,
            {0,0,(float) selectCharacter->width, (float) selectCharacter->height} ,
            {screenWidth * 0.6f, screenHeight * 0.4f,  300, 450},
            {0,0}, 0, WHITE);
}