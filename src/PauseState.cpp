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


void PauseState::update(float deltatime){
    for(auto& button: buttons){
        button->update();
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