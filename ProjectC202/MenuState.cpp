#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"
void MenuState::handleInput(Game& game){

}

void MenuState::init(Game& game ){
    buttons.push_back(Button(screenWidth / 2, screenHeight / 2, 100, 50, "PLAY", RED, BLUE, GREEN));
    buttons.push_back(Button(screenWidth / 2, screenHeight * 0.7f, 100, 50, "EXIT", RED, BLUE, GREEN));
    
}

void MenuState::update(Game& game){
    for(auto& button: buttons){
        button.update();
    }

    if(buttons[0].IsClicked()){
        game.changeState(new PlayState());
    }
    else if(buttons[1].IsClicked()){
        exit(0);
    }
}

void MenuState::render(Game& game){
    for(auto& button: buttons){
        button.draw();
    }
}