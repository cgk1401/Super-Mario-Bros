#include "../headers/PlayState.h"
#include "../headers/Game.h"
#include "../headers/MenuState.h"

PlayState::PlayState() {
    gui = GUI();
    isPlaying = true;
}
PlayState::~PlayState() {

}
void PlayState::handleInput(Game& game){

}
void PlayState::update(Game& game){
    if (gui.PauseButton_IsPressed() && isPlaying) {
        isPlaying = false;
    }
    else {
        if (pauseMenu.resume_IsCLicked()) {
            isPlaying = true;
        }
        else if (pauseMenu.save_IsCLicked()) {
            //save map
        }
    }
    if (isPlaying) {
        gui.update(game); 
    }
    else {
        pauseMenu.update(game);  
    }
}

void PlayState::render(){
    gui.draw();
    if(isPlaying == false) {
        pauseMenu.render();
    }
}