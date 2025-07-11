#include "../headers/PlayState.h"
#include "../headers/Game.h"
#include "../headers/MenuState.h"
#include "../headers/EffectManager.h"
#include "../headers/EnemyFactory.h"
#include "../headers/Collision.h"
#include "../headers/ItemManager.h"
#include "../headers/SoundManager.h"
PlayState::PlayState() {
    SoundManager::get()->playMusic(MusicType::MAIN_THEME_OVERWORLD);
    gui = GUI();
 
    map = new Map("../assets/Map/tileset_gutter64x64.png");
    map->loadFromFile("map1.txt");
    camera.init({0,0});
    bg.addLayer("../assets/Map/Layers/back.png",{0, 55 , 144, 108}, 0.05, 7.2);
    bg.addLayer("../assets/Map/Layers/far.png", { 0, 55 , 144, 108 }, 0.1, 7.2);
    bg.addLayer("../assets/Map/Layers/middle.png", { 0, 55 , 144, 108 }, 0.2, 7.2);
    
    enemies.push_back(EnemyFactory::createEnemy(EnemyType::GOOMBA, {100, 100}));
    enemies.push_back(EnemyFactory::createEnemy(EnemyType::KOOPA, {200, 100}));
    enemies.push_back(EnemyFactory::createEnemy(EnemyType::PIRANT_PLANT, {300, 100}));
    //fg.addLayer("../assets/Map/Layers/foreground.png", { 0, 34 , 176, 132 }, 0.01, 7);
   /* mario = Mario({ 50, 50 });*/
}
PlayState::~PlayState() {
    delete map;
    bg.unload();
    ItemManager::get().clearItems();
    SoundManager::get()->stopMusic();
}

void PlayState::update(float dt){
    SoundManager::get()->updateMusic();
    if (gui.PauseButton_IsPressed()) {       
        Game::getInstance()->addState(new PauseState());
    }


    camera.update(mario->getBound(), screenWidth);
    gui.update(); 
    //bg.update( mario,camera.getCamera(), dt);
    //fg.update( mario,camera.getCamera(), dt);
    //mario.Update(dt, map);
    map->update();
        
    mario->Update(dt);
    Collision::handlePlayerCollision(mario, map);
    EffectManager::get().update(dt);
    ItemManager::get().Update(dt, mario, map);

    for(auto& e: enemies){
        e->Update(dt, map);
    }
    

    //remove if any enemies die
    enemies.erase(remove_if(enemies.begin(), enemies.end(),
        [](Enemy* e) {
            if (e->isDead()) {
                delete e;
                return true;
            }
    return false;
    }),
    enemies.end());
    
}

void PlayState::render() {
    BeginMode2D(camera.getCamera());
    //bg.draw();
    ItemManager::get().Draw();
    map->draw();
    mario->Draw();
    for(auto& e: enemies){
        e->Draw();
    }
    EffectManager::get().draw();
    //fg.draw();
    EndMode2D();

    gui.draw();
    
}