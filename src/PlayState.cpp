#include "../headers/PlayState.h"
#include "../headers/Game.h"
#include "../headers/MenuState.h"

PlayState::PlayState() {
    gui = GUI();
    isPlaying = true;
    map = new Map("../assets/Map/tileset_gutter64x64.png");
    map->loadFromFile("map1.txt");
    camera.offset = { 0,0 };
    camera.target = { 0, 0 };
    camera.rotation = 0;
    camera.zoom = 1.0;
}
PlayState::~PlayState() {
    delete map;
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

    map->update(camera);
}

void PlayState::render(){
    map->draw(camera); // add camera cua mario
    gui.draw();
    if(isPlaying == false) {
        pauseMenu.render();
    }
    
}