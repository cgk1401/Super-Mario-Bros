#include "../headers/PlayState.h"
#include "../headers/Game.h"
#include "../headers/MenuState.h"
#include "../headers/EffectManager.h"
#include "../headers/EnemyFactory.h"
#include "../headers/Collision.h"
#include "../headers/ItemManager.h"
#include "../headers/SoundManager.h"
#include "../headers/Luigi.h"

PlayState::PlayState(pair<int, int> _level, HUD* _hud) {
    if (_level == pair {1,1})      Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_OVERWORLD, true);
    else if (_level == pair {1,2}) Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_UNDERGROUND, true);
    else if (_level == pair {1,3}) Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_OVERWORLD, true);
    else if (_level == pair {1,4}) Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_CASTLE, true);

    if (selectedCharacter == CharacterType::Mario) {
        character = new Mario({ 100, 300 });
    }
    else if (selectedCharacter == CharacterType::Luigi) {
        character = new Luigi({ 100, 300 });
    }
    
    Global::character = character;
    lift = new VerticalLift({ 500, 700 });

    level = _level;
    Global::level = _level;
    world[level] = new Map(level);
    
    world[level]->setEnemySpawnCallback(
        [this](EnemyType type, Vector2 pos, MapTheme theme) {
            enemies.push_back(EnemyFactory::createEnemy(type, pos, theme));
        }
    );
    hud = _hud;
    if(!hud) hud = new HUD(level);

    Singleton<ItemManager>::getInstance().clearItems();
    world[level]->loadFromFile(level);
    Global::map = world[level];
    camera.init({0,0});

    EffectManager* effects = &Singleton<EffectManager>::getInstance();
    
    character->attachObserver(this);
    character->attachObserver(hud);
    character->attachObserver(effects);

    bg.addLayer("../assets/Map/Layers/back.png",{0, 55 , 144, 108}, 0.05, 9.2);
    bg.addLayer("../assets/Map/Layers/far.png", { 0, 55 , 144, 108 }, 0.1, 9.2);
    bg.addLayer("../assets/Map/Layers/middle.png", { 0, 55 , 144, 108 }, 0.2, 9.2);
    
    //fg.addLayer("../assets/Map/Layers/foreground.png", { 0, 34 , 176, 132 }, 0.01, 7);
    PauseButton = new Button("../assets/GUI/Pause Button.png", screenWidth * 0.03f, screenHeight * 0.02f, 75, 75, "", WHITE, 40);

   cutscene.play(new ScreenEffectCutscene(SreenType::NONE, BLACK, 3, TextFormat("ROUND %d - %d\n Lives: x%d", level.first, level.second, hud->getLives())));
   if (level == pair{1,1}) cutscene.play(new KidnapCutscene);
}
PlayState::~PlayState() {
    for (auto& [level, mapPtr] : world) {  
            delete mapPtr;
            mapPtr = nullptr;
    }
    world.clear();
    bg.unload();
}

void PlayState::handleInput() {
    
    if (PauseButton->IsClicked()) {
        Singleton<Game>::getInstance().addState(new PauseState());
        shouldExit = true;
    }
    if(cutscene.isActive()){
        return;
    }
}

void PlayState::update(float dt){
    if(cutscene.isActive()){
        cutscene.update(dt);
        return;
    }

    ///______________________________WOLRD__________________________________________
    camera.update(character->getBound(), world[level]->columns * Map::TILE_SIZE);
    Global::camera = camera.getCamera();
    PauseButton->update(dt);
    bg.update({character->getBound().x, character->getBound().y},camera.getCamera(), dt);
    //fg.update( mario,camera.getCamera(), dt);
    world[level]->update();

    ///______________________________ENTITIES__________________________________________
    Collision::handlePlayerCollision(character, world[level]);
    lift->Update(dt);

    if (character->getCurrentAction() != ActionState::Die) {
        Singleton<SoundManager>::getInstance().updateMusic();
        character->HandleInput(dt);
        character->Update(dt);
        hud->update(dt); 
        Singleton<ItemManager>::getInstance().Update(dt, character, world[level]);
    }
    else {
        if (newRound_countDown.isRunning()) {
            newRound_countDown.update(dt);
            if (newRound_countDown.isFinished()) {
                if(hud->getLives() <= 0){
                    //trigger a GAMEOVER scene
                    cutscene.play(new ScreenEffectCutscene(SreenType::NONE, BLACK, 5.5, "GAME OVER"));
                    Singleton<SoundManager>::getInstance().play(SoundType::GAMEOVER1);
                }
                else Singleton<Game>::getInstance().replaceState(new PlayState(level, hud));
                return;
            }
        }
        
        if(newRound_countDown.isFinished()){
            Singleton<Game>::getInstance().changeState(new PlayState(level));
            return;
        }
    }
    Collision::handlePlayer_EnemyCollision(character, enemies);
   
    Singleton<EffectManager>::getInstance().update(dt);

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

    //for (auto e : enemies) {
    //    if (Bowser* bowser = dynamic_cast<Bowser*> (e) ){
    //        for (auto ball : bowser->getBowserFireball()) {
    //            Collision::handleBowserball_CharacterCollision(ball, character);
    //        }
    //    }
    //}
    ///______________________________DELETION__________________________________________
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
    ///______________________________WORLD__________________________________________
    BeginMode2D(camera.getCamera());
    Singleton<EffectManager>::getInstance().drawHiddenEffects();
    Singleton<ItemManager>::getInstance().DrawHiddenItem();
    world[level]->draw();
    if (character->getCurrentAction() != ActionState::Die) {
        Tile tile = world[level]->getTile(character->getBound().y / Map::TILE_SIZE, character->getBound().x / Map::TILE_SIZE);
        if (tile.type != TileType::BLACK_BLOCK) character->Draw();
    }
    for(auto& e: enemies){
        e->Draw();
    }
    lift->Draw();
    Singleton<EffectManager>::getInstance().draw();
    Singleton<ItemManager>::getInstance().Draw();
    //fg.draw();
    EndMode2D();

    ///______________________________GUI________________________________________
    hud->draw();
    PauseButton->draw();
    if(cutscene.isActive()) cutscene.draw();
}

void PlayState::ChangeCharacter(CharacterType newtype) {
    if (character->getCharacterType() != newtype) {
        delete character;
        if (newtype == CharacterType::Mario) character = new Mario({ 100, 200 });
        else if (newtype == CharacterType::Luigi) character = new Luigi({ 100, 200 });
    }
}


void PlayState::onNotify(const EventType& event, void* data){
    if(event == EventType::ON_DEATH){
        newRound_countDown.start(4);
    }
    else if (event == EventType::FLAG_POLE){
       cutscene.play(new FlagPoleCutscene(character, hud, world[level], camera));
    
    }
}