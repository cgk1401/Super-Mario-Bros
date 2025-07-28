#include "../headers/CharacterSelection.h"
#include "../headers/PlayState.h"
#include "../headers/MenuState.h"

CharacterSelection::CharacterSelection() {
    font = LoadFont("../assets/font/knightwarrior.otf");

    backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);
    play_button = new Button(Singleton<TextureManager>::getInstance().load(TextureType::BUTTON), screenWidth, screenHeight * 0.85f, screenWidth / 3 * 0.5f, screenHeight * 0.25f * 0.5f, "PLAY", WHITE, 35);

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
    Singleton<SoundManager>::getInstance().updateMusic();
    for (auto& choice : characterChoices) {
        choice->update(deltatime);
    }
    
    speed = approach(speed, 0 , 0.2);
    float posX = play_button->getBounds().x;
    float posY = play_button->getBounds().y;
    posX = approach(posX, screenWidth * 0.8f, speed);
    play_button->updatePos({posX, posY});

    play_button->update(deltatime);
    backButton->update(deltatime);
    if (selectedCharacter == CharacterType::Mario) {
        characterChoices[0]->updateScale(1.1f);
    }
    else if (selectedCharacter == CharacterType::Luigi) {
        characterChoices[1]->updateScale(1.1f);
    }
    if (characterChoices[0]->IsClicked()) {
        selectCharacter = &characters[0];
        selectedCharacter = CharacterType::Mario;
    }
    else if (characterChoices[1]->IsClicked()) {
        selectCharacter = &characters[1];
        selectedCharacter = CharacterType::Luigi;
        
    }
    else if(play_button->IsClicked()){
        Singleton<Game>::getInstance().changeState(new PlayState({1,1}));
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
    DrawTexturePro(*selectCharacter,
        { 0,0,(float)selectCharacter->width, (float)selectCharacter->height },
        { screenWidth * 0.55f, screenHeight * 0.15f, screenHeight / (1.18f * 1.5f), screenHeight / 1.18f },
        { 0,0 }, 0, Fade(BLUE, 0.2f));
    backButton->draw();
    play_button->draw();
    for (auto& choice : characterChoices) {
        choice->draw();
    }

    float offset = 100;
    if (selectedCharacter == CharacterType::Mario) {
        Rectangle optionBound = characterChoices[0]->getBounds();
        DrawTriangle({ optionBound.x - 50, optionBound.y + optionBound.height / 2 - 50}, { optionBound.x - 50, optionBound.y + optionBound.height / 2 + 50 }, { optionBound.x - 25, optionBound.y + optionBound.height / 2  }, RED);
    }
    else if (selectedCharacter == CharacterType::Luigi) {
        Rectangle optionBound = characterChoices[1]->getBounds();
        DrawTriangle({ optionBound.x - 50, optionBound.y + optionBound.height / 2 - 50 }, { optionBound.x - 50, optionBound.y + optionBound.height / 2 + 50 }, { optionBound.x - 25, optionBound.y + optionBound.height / 2 }, GREEN);

    }
    //HEADER TITLE
    //DrawTextEx(font, "MARIO MARIO", { screenWidth * 0.33f, screenHeight * 0.1f }, 100, 5, DARKBROWN);
   
    DrawTexturePro(*selectCharacter,
            {0,0,(float) selectCharacter->width, (float) selectCharacter->height} ,
            {screenWidth * 0.5f, screenHeight * 0.3f, 350 , 525},
            {0,0}, 0, WHITE);
    
}