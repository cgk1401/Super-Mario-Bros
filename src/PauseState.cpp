#include "../headers/PauseState.h"
#include "../headers/Global.h"
#include "../headers/MenuState.h"
#include "../headers/PlayState.h"

PauseState::PauseState() {
    buttons.resize(4);
    buttons[0] = new Button("../assets/GUI/Button.png", screenWidth * 0.34f, screenHeight * 0.2f, screenWidth / 3, screenHeight * 0.15f, "RESUME", WHITE, 40);
    buttons[1] = new Button("../assets/GUI/Button.png", screenWidth * 0.34f, screenHeight * 0.35f + 5, screenWidth / 3, screenHeight * 0.15f, "RESTART", WHITE, 40);
    buttons[2] = new Button("../assets/GUI/Button.png", screenWidth * 0.34f, screenHeight * 0.5f + 10, screenWidth / 3, screenHeight * 0.15f, "SAVE", WHITE, 40);
    buttons[3] = new Button("../assets/GUI/Button.png", screenWidth * 0.34f, screenHeight * 0.65f + 15, screenWidth / 3, screenHeight * 0.15f, "MENU", WHITE, 40);

 
}

PauseState::~PauseState() {
    for (auto& button : buttons) {
        delete button;
    }
}

void PauseState::handleInput(Game& game) {
    
}

bool PauseState::resume_IsCLicked() {
    return buttons[0]->IsClicked();
}

bool PauseState::save_IsCLicked() {
    return buttons[2]->IsClicked();
}

void PauseState::update(Game& game){
    for(auto& button: buttons){
        button->update();
    }

    //Button Clicking
    if(buttons[3]->IsClicked()){ //Menu 
        game.changeState(new MenuState());
    }
    else if (buttons[1]->IsClicked()) {
        game.changeState(new PlayState());
    }

}
void PauseState::render(){
    DrawRectangleRec(Rectangle{0, 0, screenWidth, screenHeight}, Fade(BLACK, 0.6f));
    for(auto& button: buttons){
        button->draw();
    }
}