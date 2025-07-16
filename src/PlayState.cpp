#include "../headers/PlayState.h"
#include "../headers/Game.h"
#include "../headers/MenuState.h"
#include "../headers/EffectManager.h"
#include "../headers/EnemyFactory.h"
#include "../headers/Collision.h"
#include "../headers/ItemManager.h"
#include "../headers/SoundManager.h"
PlayState::PlayState() {
    Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_OVERWORLD);
    gui = GUI();
 
    map = new Map("../assets/Map/tileset_gutter64x64.png");

    map->setEnemySpawnCallback(
        [this](EnemyType type, Vector2 pos) {
            enemies.push_back(EnemyFactory::createEnemy(type, pos));
        }
    );

    map->loadFromFile("map1.txt");
    Global::map = map;
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
    Singleton<ItemManager>::getInstance().clearItems();
    Singleton<SoundManager>::getInstance().stopMusic();
}

void PlayState::update(float dt){
    //SoundManager::get()->updateMusic();
    if (gui.PauseButton_IsPressed()) {       
        Singleton<Game>::getInstance().addState(new PauseState());
    }


    camera.update(mario->getBound(), screenWidth);
    gui.update(); 
    //bg.update( mario,camera.getCamera(), dt);
    //fg.update( mario,camera.getCamera(), dt);
    map->update();
    Collision::handlePlayerCollision(mario, map);
    mario->Update(dt);
   
    Singleton<EffectManager>::getInstance().update(dt);
    Singleton<ItemManager>::getInstance().Update(dt, mario, map);

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
    
     Global::camera = camera.getCamera();
}

void PlayState::render() {
    BeginMode2D(camera.getCamera());
    //bg.draw();
    Singleton<ItemManager>::getInstance().Draw();
    map->draw();
    mario->Draw();
    DrawRectangleLinesEx(mario->getBound(), 0.5, RED);
    for(auto& e: enemies){
        e->Draw();
    }
    Singleton<EffectManager>::getInstance().draw();
    //fg.draw();
    EndMode2D();

    gui.draw();
    
}