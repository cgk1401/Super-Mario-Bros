#include "../headers/MenuState.h"
#include "../headers/Game.h"
#include "../headers/PlayState.h"

MenuState::MenuState() {
    TraceLog(LOG_INFO, "Menu: Constructor");
    buttons.resize(3);
    buttons[0] = new Button("../assets/GUI/Button.png", screenWidth * 0.35f, screenHeight * 0.25, screenWidth / 3, screenHeight / 5, "PLAY", WHITE, 40);
    buttons[1] = new Button("../assets/GUI/Button.png",screenWidth * 0.35f, screenHeight *0.25 + screenHeight / 5 + 5, screenWidth / 3, screenHeight / 5, "SETTINGS", WHITE, 40);
    buttons[2] = new Button("../assets/GUI/Button.png", screenWidth * 0.35f, screenHeight * 0.25 + 2 * screenHeight / 5 + 10, screenWidth / 3, screenHeight / 5, "EXIT", WHITE, 40);
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
void MenuState::handleInput(Game& game){

}

void MenuState::update(Game& game){
    for(auto& button: buttons){
        button->update();
    }

    if(buttons[0]->IsClicked()){
        game.changeState(new PlayState());
    }
    else if(buttons[2]->IsClicked()){
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