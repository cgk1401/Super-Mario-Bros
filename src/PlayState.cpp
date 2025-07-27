#include "../headers/PlayState.h"
#include "../headers/Game.h"
#include "../headers/MenuState.h"
#include "../headers/EffectManager.h"
#include "../headers/EnemyFactory.h"
#include "../headers/Collision.h"
#include "../headers/ItemManager.h"
#include "../headers/SoundManager.h"
#include "../headers/Luigi.h"

PlayState::PlayState(pair<int, int> _level) {
    if (_level == pair {1,2}) Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_UNDERGROUND, true);
    else Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_OVERWORLD, true);

    if (selectedCharacter == CharacterType::Mario) {
        character = new Mario({ 100, 300 });
    }
    else if (selectedCharacter == CharacterType::Luigi) {
        character = new Luigi({ 100, 300 });
    }

    EffectManager* effects = &Singleton<EffectManager>::getInstance();
    character->attachObserver(&hud);
    character->attachObserver(effects);
    
    level = _level;
    Global::level = _level;
    world[level] = new Map(level);
    
    world[level]->setEnemySpawnCallback(
        [this](EnemyType type, Vector2 pos) {
            enemies.push_back(EnemyFactory::createEnemy(type, pos));
        }
    );
    
    Singleton<ItemManager>::getInstance().clearItems();
    world[level]->loadFromFile(level);
    Global::map = world[level];
    camera.init({0,0});
   
    bg.addLayer("../assets/Map/Layers/back.png",{0, 55 , 144, 108}, 0.05, 9.2);
    bg.addLayer("../assets/Map/Layers/far.png", { 0, 55 , 144, 108 }, 0.1, 9.2);
    bg.addLayer("../assets/Map/Layers/middle.png", { 0, 55 , 144, 108 }, 0.2, 9.2);
    
    //fg.addLayer("../assets/Map/Layers/foreground.png", { 0, 34 , 176, 132 }, 0.01, 7);
   /* mario = Mario({ 50, 50 });*/
   PauseButton = new Button("../assets/GUI/Pause Button.png", screenWidth * 0.03f, screenHeight * 0.02f, 75, 75, "", WHITE, 40);
}
PlayState::~PlayState() {
    for (auto& [level, mapPtr] : world) {  
            delete mapPtr;
            mapPtr = nullptr;
    }
    world.clear();

    bg.unload();
}

void PlayState::update(float dt){
    

    camera.update(character->getBound(), world[level]->columns * Map::TILE_SIZE);
    hud.update(); 
    PauseButton->update(dt);
    if (PauseButton->IsClicked()) {       
        Singleton<Game>::getInstance().addState(new PauseState());
    }

    bg.update({character->getBound().x, character->getBound().y},camera.getCamera(), dt);
    //fg.update( mario,camera.getCamera(), dt);
    world[level]->update();

    Collision::handlePlayerCollision(character, world[level]);

    if (character->getCurrentAction() != ActionState::Die) {
        Singleton<SoundManager>::getInstance().updateMusic();
        character->Update(dt);
    }
    Collision::handlePlayer_EnemyCollision(character, enemies);

   
    Singleton<EffectManager>::getInstance().update(dt);
    Singleton<ItemManager>::getInstance().Update(dt, character, world[level]);

    Collision::handleEnemy_EnemyCollison(enemies);
    for(auto& e: enemies){
        Collision::handleEnemyCollision(e, world[level]);
        if(e->isActive()) e->Update(dt, world[level]);
    }
    
    FireState* fireState = dynamic_cast<FireState*>(character->GetCurrentState());
    if (fireState) {
        auto& fireballs = fireState->getFireBall(); 
        for (auto& f : fireballs) {
            if (f) Collision::handleFireball_EnemyCollision(f, enemies);
        }
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
    // DrawTexturePro(world_1_1,
    //                { 0,0, (float) world_1_1.width, (float) world_1_1.height},
    //                {0 * Map::TILE_SIZE, -2 * Map::TILE_SIZE,  (float) world_1_1.width * 4, (float) world_1_1.height * 4},
    //                {0,0}, 0,
    //                Fade(WHITE, 0.4f));
    Singleton<EffectManager>::getInstance().drawHiddenEffects();

    Singleton<ItemManager>::getInstance().Draw();
    world[level]->draw();
    
    if (character->getCurrentAction() != ActionState::Die) character->Draw();
    //DrawRectangleLinesEx(character->getBound(), 0.5, RED);
    for(auto& e: enemies){
        e->Draw();
    }
     Singleton<EffectManager>::getInstance().draw();
    //fg.draw();
    EndMode2D();

    hud.draw();
    PauseButton->draw();
}

void PlayState::ChangeCharacter(CharacterType newtype) {
    if (character->getCharacterType() != newtype) {
        delete character;
        if (newtype == CharacterType::Mario) character = new Mario({ 100, 200 });
        else if (newtype == CharacterType::Luigi) character = new Luigi({ 100, 200 });
    }
}
