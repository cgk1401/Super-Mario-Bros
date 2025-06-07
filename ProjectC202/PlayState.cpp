#include "PlayState.h"
#include "Game.h"
#include "MenuState.h"

void PlayState::handleInput(Game& game){

}

void PlayState::init(Game& game ){
   gui.init();
   pause_button.init(game);
   isPlaying = true;
}

void PlayState::update(Game& game){
    if(gui.PauseButton_IsPressed()) isPlaying = false;
    if(isPlaying == false) pause_button.update(game);
    else gui.update(game);
}

void PlayState::render(Game& game){
    gui.draw();
    if(isPlaying == false) {
        pause_button.render(game);
    }
}