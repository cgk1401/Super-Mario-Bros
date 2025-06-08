#include "../headers/PauseState.h"
#include "../headers/Global.h"
#include "../headers/MenuState.h"
 void PauseState::handleInput(Game& game) {

 }

void PauseState::init(Game& game ) {
    buttons.push_back(Button(screenWidth * 0.4f, screenHeight / 2, 100, 50, "RESUME", RED, BLUE, GREEN));
    buttons.push_back(Button(screenWidth * 0.4f, screenHeight * 0.7f, 100, 50, "MENU", RED, BLUE, GREEN));
}

void PauseState::update(Game& game){
    for(auto& button: buttons){
        button.update();
    }

    if(buttons[1].IsClicked()){ //Menu 
        game.changeState(new MenuState());
    }
}
void PauseState::render(Game& game){
    for(auto& button: buttons){
        button.draw();
    }
}