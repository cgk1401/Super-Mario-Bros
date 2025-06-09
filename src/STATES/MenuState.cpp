#include "STATES/MenuState.h"
#include "GAME/Game.h"
#include "STATES/PlayState.h"
void MenuState::handleInput(Game& game){

}

void MenuState::init(Game& game ){
    buttons.push_back(Button(screenWidth / 2, screenHeight / 2, 100, 50, "PLAY", RED, BLUE, GREEN));
}

void MenuState::update(Game& game){
    for(auto& button: buttons){
        button.update();
    }

    for(auto& button: buttons){
        if(button.IsClicked()){
            game.changeState(new PlayState());
        }
    }
}

void MenuState::render(Game& game){
    for(auto& button: buttons){
        button.draw();
    }
}