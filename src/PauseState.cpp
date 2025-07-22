#include "../headers/PauseState.h"
#include "../headers/Global.h"
#include "../headers/MenuState.h"
#include "../headers/PlayState.h"

PauseState::PauseState() {
    int amount_button = 4;
    buttons.resize(amount_button);

    ButtonLayoutConfig cfg(amount_button);
    const char* buttonLabels[4] = { "RESUME", "RESTART", "SAVE", "MENU" };
    buttons = CreateButtons(buttonLabels, cfg);
}

PauseState::~PauseState() {
    for (auto& button : buttons) {
        delete button;
    }
}


void PauseState::update(float deltatime){
    for(auto& button: buttons){
        button->update(deltatime);
    }

    //Button Clicking
    if(buttons[3]->IsClicked()){ //Menu 
        Singleton<Game>::getInstance().clear();
        Singleton<Game>::getInstance().addState(new MenuState);
    }
    else if (buttons[1]->IsClicked()) { //Restart
        Singleton<Game>::getInstance().clear();
        Singleton<Game>::getInstance().addState(new PlayState);
    }
    else if (buttons[0]->IsClicked()) {
        Singleton<Game>::getInstance().pop();
    }


}
void PauseState::render(){
    DrawRectangleRec(Rectangle{0, 0, screenWidth, screenHeight}, Fade(BLACK, 0.6f));
    for(auto& button: buttons){
        button->draw();
    }
}