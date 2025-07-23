#include "../headers/CharacterSelection.h"
#include "../headers/PlayState.h"
#include "../headers/MenuState.h"

CharacterSelection::CharacterSelection() {

    font = LoadFont("../assets/font/knightwarrior.otf");

    backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);

    background = LoadTexture("../assets/GUI/Character_Seletion.png");
    characters.resize(2);
    characters[0] = LoadTexture("../assets/GUI/menu_mario.png");
    characters[1] = LoadTexture("../assets/GUI/menu_luigi.png");
    selectCharacter = selectedCharacter == CharacterType::Mario ? &characters[0] : &characters[1];

    characterChoices.resize(2);
    characterChoices[0] = new Button("../assets/GUI/characterselection_mario.png",  screenWidth * 0.13f, screenHeight * 0.15, 250,309, "", WHITE, 0, "MARIO");
    characterChoices[1] = new Button("../assets/GUI/characterselection_luigi.png",  screenWidth * 0.13f, screenHeight * 0.15 + 309 + 12, 250,309, "", WHITE, 0, "LUIGI");
}

CharacterSelection::~CharacterSelection() {
    for (auto& character : characters) UnloadTexture(character);
    for(auto& choice: characterChoices) delete choice;
    delete backButton;

    UnloadTexture(background);
    UnloadFont(font);
}

void CharacterSelection::update(float deltatime) {
    for (auto& choice : characterChoices) {
        choice->update(deltatime);
    }
    backButton->update(deltatime);

    if (characterChoices[0]->IsClicked()) {
        selectCharacter = &characters[0];
        selectedCharacter = CharacterType::Mario;
    }
    else if (characterChoices[1]->IsClicked()) {
        selectCharacter = &characters[1];
        selectedCharacter = CharacterType::Luigi;
        
    }
    else if (backButton->IsClicked()) {
        Singleton<Game>::getInstance().pop();
    }
    
}

void CharacterSelection::render() {
    DrawTexturePro(background,
                {0,0, (float) background.width,(float) background.height},
                {0,0, screenWidth, screenHeight},
                 {0, 0}, 0, WHITE);
    backButton->draw();
    for (auto& choice : characterChoices) {
        choice->draw();
    }
    //HEADER TITLE
    //DrawTextEx(font, "MARIO MARIO", { screenWidth * 0.33f, screenHeight * 0.1f }, 100, 5, DARKBROWN);
    DrawTexturePro(*selectCharacter,
            {0,0,(float) selectCharacter->width, (float) selectCharacter->height} ,
            {screenWidth * 0.5f, screenHeight * 0.3f, 350 , 525},
            {0,0}, 0, WHITE);
}