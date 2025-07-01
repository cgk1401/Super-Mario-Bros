#include "../headers/PlayState.h"
#include "../headers/Game.h"
#include "../headers/MenuState.h"
#include "../headers/EffectManager.h"

PlayState::PlayState() {
    gui = GUI();
    isPlaying = true;
    map = new Map("../assets/Map/tileset_gutter64x64.png");
    map->loadFromFile("map1.txt");
    camera.init({0,0});
    bg.addLayer("../assets/Map/Layers/back.png",{0, 55 , 144, 108}, 0.05, 7.2);
    bg.addLayer("../assets/Map/Layers/far.png", { 0, 55 , 144, 108 }, 0.1, 7.2);
    bg.addLayer("../assets/Map/Layers/middle.png", { 0, 55 , 144, 108 }, 0.2, 7.2);
    
    //fg.addLayer("../assets/Map/Layers/foreground.png", { 0, 34 , 176, 132 }, 0.01, 7);
   /* mario = Mario({ 50, 50 });*/
}
PlayState::~PlayState() {
    delete map;
    bg.unload();
}
void PlayState::handleInput(Game& game){

}
void PlayState::update(Game& game){
    float dt = GetFrameTime();
    

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
        camera.update(mario.getBound(), screenWidth);
        gui.update(game); 
        bg.update( mario,camera.getCamera(), dt);
        //fg.update( mario,camera.getCamera(), dt);
        mario.Update(GetFrameTime(), map);
        map->update();
        EffectManager::get().update(dt);
    }
    else {
        pauseMenu.update(game);  
    }

    
}

void PlayState::render() {
    BeginMode2D(camera.getCamera());
    //bg.draw();
   
    map->draw();
    EffectManager::get().draw();
    mario.Draw();
    //fg.draw();
    EndMode2D();

    gui.draw();
    if(isPlaying == false) {
        pauseMenu.render();
    }
   
    
}