#include "STATES/PlayState.h"
#include "GAME/Game.h"
#include "STATES/MenuState.h"

void PlayState::handleInput(Game& game){

}

void PlayState::init(Game& game ){
   gui = GUI();
}

void PlayState::update(Game& game){
    if(IsKeyPressed(KEY_P)){
        game.changeState(new MenuState());
    }
}

void PlayState::render(Game& game){
    gui.draw();
}