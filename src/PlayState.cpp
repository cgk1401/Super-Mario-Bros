#include "../headers/PlayState.h"
#include "../headers/Game.h"
#include "../headers/MenuState.h"

PlayState::PlayState() {
    gui = GUI();
    isPlaying = true;
    map = new Map("../assets/Map/tileset_gutter64x64.png");
    map->loadFromFile("map1.txt");
    camera.offset = { 0,0 };
    camera.target = { 0,0 };
    camera.rotation = 0;
    camera.zoom = 1.0;

   /* mario = Mario({ 50, 50 });*/
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
        mario.Update(GetFrameTime(), map);
        map->update(camera);
    }
    else {
        pauseMenu.update(game);  
    }

    
}

void PlayState::render(){
   // camera.target = mario.getPos();
    map->draw(camera); // add camera 
    gui.draw();
    mario.Draw();
    

    if(isPlaying == false) {
        pauseMenu.render();
    }
    
}