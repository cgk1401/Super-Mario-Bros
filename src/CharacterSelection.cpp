#include "../headers/CharacterSelection.h"
#include "../headers/PlayState.h"
#include "../headers/MenuState.h"

CharacterSelection::CharacterSelection() {
    const int amount_button = 3;
    buttons.resize(amount_button);

    ButtonLayoutConfig cfg(amount_button);
    const char* buttonLabels[amount_button] = { "Mario", "Luigi", "Return menu"};
   
    buttons = CreateButtons(buttonLabels, cfg);
    font = LoadFont("../assets/font/knightwarrior.otf");

    background = resizedImage("../assets/GUI/Menu Background.png", screenWidth, screenHeight);
    characters.resize(2);
    characters[0] = resizedImage("../assets/GUI/Menu Mario.png", 400, 400);
    characters[1] = resizedImage("../assets/GUI/Luigi.png", 400, 400);
    selectCharacter = &characters[0];
}

CharacterSelection::~CharacterSelection() {
    for (auto& button : buttons) delete button;
    for (auto& character : characters) UnloadTexture(character);

    UnloadTexture(background);
    UnloadFont(font);
}

void CharacterSelection::update(float deltatime) {
    for (auto& button : buttons) {
        button->update();
    }

    if (buttons[0]->IsClicked()) {
        selectCharacter = &characters[0];
        selectedCharacter = CharacterType::Mario;
    }
    else if (buttons[1]->IsClicked()) {
        selectCharacter = &characters[1];
        selectedCharacter = CharacterType::Luigi;
        
    }
    else if (buttons[2]->IsClicked()) {
        Singleton<Game>::getInstance().replaceState(new MenuState());
    }
    
}

void CharacterSelection::render() {
    DrawTexture(background, 0, 0, WHITE);

    for (auto& button : buttons) {
        button->draw();
    }
    //HEADER TITLE
    DrawTextEx(font, "MARIO MARIO", { screenWidth * 0.33f, screenHeight * 0.1f }, 100, 5, DARKBROWN);
    DrawTexture(*selectCharacter, screenWidth * 0.6f, screenHeight * 0.4f, WHITE);
}