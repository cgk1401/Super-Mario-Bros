#include "../headers/PlayState.h"
#include "../headers/Game.h"
#include "../headers/MenuState.h"
#include "../headers/EffectManager.h"
#include "../headers/EnemyFactory.h"
#include "../headers/Collision.h"
#include "../headers/ItemManager.h"
#include "../headers/SoundManager.h"
#include "../headers/Luigi.h"
#include "CUTSCENES/PipeCutscene.h"
#include "nlohmann/json.hpp"
#include "CUTSCENES/PrincessRescueCutscene.h"
#include "EnemyFactory.h"
#include "LevelCompleteState.h"
PlayState::PlayState(pair<int, int> _level, HUD* _hud, Character* _character, const char* _extraMap_filename) {
    if (_level == pair {1,1})      Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_OVERWORLD, true);
    else if (_level == pair {1,2}) Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_UNDERGROUND, true);
    else if (_level == pair {1,3}) Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_OVERWORLD, true);
    else if (_level == pair {1,4}) {
        Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_CASTLE, true);
        princess = new Princess({9720, 688});
    }

    if (selectedCharacter == CharacterType::Mario) {
        character = new Mario({ 100, 300 });
    }
    else if (selectedCharacter == CharacterType::Luigi) {
        character = new Luigi({ 100, 300 });
    }
    
    Global::character = character;

    level = _level;
    Global::level = _level;
    world[level] = new Map(level);
    
    if(_hud) hud = _hud;
    else hud = new HUD(level);
    
    spawnEnemy();
    Singleton<ItemManager>::getInstance().clearItems();

     string filename;
    if(!_extraMap_filename){
       
        filename = "map" + to_string(level.first) + "_" + to_string(level.second) + ".txt"; //e.g. map1_1.txt, map1_2.txt
       
    }
    else filename = _extraMap_filename;
     world[level]->loadFromFile(filename.c_str());
    Global::map = world[level];
    camera.init({0,0});

    EffectManager* effects = &Singleton<EffectManager>::getInstance();
    
    if (_character) {
        character = _character;
        character->deleteAllObservers();
        character->setPosition({ 100, 300 });
    }
    else {
        Vector2 startPoint = { 100, 300 };
        if (level == pair{ 1,1 }) startPoint = { 100, 12 * Map::TILE_SIZE };

        if (selectedCharacter == CharacterType::Mario) {
            character = new Mario(startPoint);
        }
        else if (selectedCharacter == CharacterType::Luigi) {
            character = new Luigi(startPoint);
        }
    }

    character->attachObserver(this);
    character->attachObserver(hud);
    character->attachObserver(effects);
    
    bg.addLayer("../assets/Map/Layers/back.png",{0, 55 , 144, 108}, 0.05, 9.2);
    bg.addLayer("../assets/Map/Layers/far.png", { 0, 55 , 144, 108 }, 0.1, 9.2);
    bg.addLayer("../assets/Map/Layers/middle.png", { 0, 55 , 144, 108 }, 0.2, 9.2);
    
    fg.addLayer("../assets/Map/Layers/foreground.png", { 0, 34 , 176, 132 }, 0.01, 7);
    PauseButton = new Button("../assets/GUI/Pause Button.png", screenWidth * 0.03f, screenHeight * 0.02f, 75, 75, "", WHITE, 40);

   if(level.first >= 1 || !_extraMap_filename) cutscene.play(new ScreenEffectCutscene(SreenType::NONE, BLACK, 3, TextFormat("ROUND %d - %d\n Lives: x%d", level.first, level.second, hud->getLives())));
   if (level == pair{1,1}) cutscene.play(new KidnapCutscene(world[level], character));
}

PlayState::PlayState(const char* filename){
    Singleton<ItemManager>::getInstance().clearItems();
    loadGame(filename);
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

}
PlayState::~PlayState() {
    /*if(level == pair{1,4}){
        delete hud;
        delete character;
        delete world[level];
    }*/
    for (auto& [level, mapPtr] : world) {
        if(mapPtr)
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
    //______________________________COLLISION DETECTION____________________________
    ///______________________________WOLRD__________________________________________
    camera.update(character->getBound(), world[level]->columns * Map::TILE_SIZE);
    Global::camera = camera.getCamera();
    PauseButton->update(dt);
    bg.update({character->getBound().x, character->getBound().y},camera.getCamera(), dt);
    fg.update( {character->getBound().x, character->getBound().y},camera.getCamera(), dt);
    world[level]->update();
    
    for(auto& e: enemies){
        if(e->isActive()) {
            //Follow player
            if(e->FollowPlayer()){
                if(character->position.x > e->position.x + 50){
                    e->changeDirection(Direction::Right);
                }
                else  e->changeDirection(Direction::Left);
            }
            e->update(dt);
        }
    }
    
  
    ///______________________________ENTITIES__________________________________________
    if (character->getCurrentAction() != ActionState::Die) {
        Singleton<SoundManager>::getInstance().updateMusic(dt);
        if(character->getCharacterStateType() !=  CharacterStateType::TransformState) character->HandleInput(dt);
        hud->update(dt); 
        character->update(dt);

        if(hud->getTime() <= 0){
            character->onDead();
        }
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
    Singleton<EffectManager>::getInstance().update(dt);
    Singleton<ItemManager>::getInstance().Update(dt, character, world[level]);

    Global::character = character;

    vector<GameObject*> allObjects;
    allObjects.push_back(character);
    allObjects.insert(allObjects.end(), enemies.begin(), enemies.end());
    vector<Item*> items = Singleton<ItemManager>::getInstance().getItems();
    allObjects.insert(allObjects.end(), items.begin(), items.end());
    FireState* fireState = dynamic_cast<FireState*>(character->GetCurrentState());
    if (fireState) {
        auto& fireballs = fireState->getFireBall(); 
        for (auto& f : fireballs) {
           allObjects.push_back(f);
        }
    }
    for(auto& object: allObjects){
        Collision::handleMapCollision(object, world[level]);
    }
    Collision::handleMultipleObjectCollisions(allObjects);

   
    if(princess &&  CheckCollisionRecs(princess->getBound(), character->getBound())){
        cutscene.play(new PrincessRescueCutscene(character, camera, princess, hud, world[level]));
        return;
    }
     if(princess) {
        princess->salute();
        princess->update(dt);
    }
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
    //bg.draw();

    world[level]->drawLayer(LayerType::BACKGROUND);
    Singleton<EffectManager>::getInstance().drawHiddenEffects();
    Singleton<ItemManager>::getInstance().DrawHiddenItem();
    
    for(auto& e: enemies){
        e->draw();
    }
    world[level]->drawLayer(LayerType::PLATFORM);
    if(princess) princess->draw();
    if (character->getCurrentAction() != ActionState::Die) {
        Tile tile = world[level]->getTile((character->getBound().y + character->getBound().height / 2) / Map::TILE_SIZE, character->getBound().x / Map::TILE_SIZE, LayerType::PLATFORM);
        if (tile.type != TileType::BLACK_BLOCK) character->draw();
    }
    
    Singleton<EffectManager>::getInstance().draw();
    Singleton<ItemManager>::getInstance().Draw();
    world[level]->drawLayer(LayerType::FOREGROUND);
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
    else if(event == EventType::COIN_COLLECT){
        Vector2* pos = static_cast<Vector2*>(data);
        if(pos)
            world[level]->removeTile(pos->y / Map::TILE_SIZE, pos->x / Map::TILE_SIZE );
    }
    else if (event == EventType::FLAG_POLE){
       cutscene.play(new FlagPoleCutscene(character, hud, world[level], camera));
    
    }
    else if(event == EventType::PIPE_ENTER){
       if(level == pair{1,2}) cutscene.play(new PipeCutscene(character, hud, world[level], "map0_2.txt" ));
    }
}

void PlayState::saveGame(const char* filename) {
    nlohmann::json j;

    // Save music playback time
    j["music"]["playtime"] = Singleton<SoundManager>::getInstance().getMusicPlayTime();

    // Save player data
    j["player"]["x"] = character->getPosition().x;
    j["player"]["y"] = character->getPosition().y - Map::TILE_SIZE;
    j["player"]["type"] = character->getCharacterType();
    j["player"]["state"] = character->getCharacterStateType();
    j["player"]["action"] = character->getCurrentAction();
    j["player"]["direction"] = character->getDirection();

    // Save HUD
    j["hud"]["score"] = hud->getScore();
    j["hud"]["coins"] = hud->getCoin();
    j["hud"]["lives"] = hud->getLives();
    j["hud"]["time"] = hud->getTime();

    // Save level info
    j["level"]["world"] = level.first;
    j["level"]["map"] = level.second;

    // Save map info
    auto* map = world[level]; 
    j["map"]["row"] = map->rows;
    j["map"]["column"] = map->columns;
    j["map"]["layerCount"] = map->numberLayers;

    const std::vector<Layer>& mapData = map->getMapData();
    for (int i = 0; i < map->numberLayers; i++) {
        const Layer& layer = mapData[i];
        nlohmann::json layerJson;

        layerJson["type"] = static_cast<int>(layer.type);
        layerJson["visible"] = layer.visible;
        layerJson["hasCollision"] = layer.hasCollision;

        for (const auto& row : layer.mapData) {
            string rowStr = "";
            for (int tile = 0; tile < row.size(); tile++ ) {
               rowStr += to_string(row[tile].tileID);
               if(tile < row.size() - 1) rowStr += " ";
            }
            layerJson["data"].push_back(rowStr);
        }
        j["map"]["layers"].push_back(layerJson); 
    }

    ofstream file(filename);
    if (file.is_open()) {
        file << setw(4) << j;
        file.close();
    } else {
        cerr << "Failed to save game to " << filename << endl;
    }
}



void PlayState::loadGame(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open save file: " << filename <<endl;
        return;
    }

    nlohmann::json j;
    file >> j;
    file.close();

    // Load level info
    level = { j["level"]["world"], j["level"]["map"] };
    
    if (level == pair {1,1})      Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_OVERWORLD, true);
    else if (level == pair {1,2}) Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_UNDERGROUND, true);
    else if (level == pair {1,3}) Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_OVERWORLD, true);
    else if (level == pair {1,4}) Singleton<SoundManager>::getInstance().playMusic(MusicType::MAIN_THEME_CASTLE, true);

    float musicPlayTime = j["music"]["playtime"];
    Singleton<SoundManager>::getInstance().setMusicPlayTime(musicPlayTime);
    // Load map data
    world[level] = new Map(level);
    spawnEnemy();
    world[level]->loadMapFromJson(j["map"]);

    // Load player state
     Vector2 pos = {
        j["player"]["x"],
        j["player"]["y"]
    };
    CharacterType type =(CharacterType) j["player"]["type"];
        if(type == CharacterType::Mario){
            character = new Mario(pos);
            selectedCharacter = CharacterType::Mario;

        }
        else if (type == CharacterType::Luigi){
            character = new Luigi(pos);
            selectedCharacter = CharacterType::Luigi;
        }
    Global::character = character;
    character->setCharacterState((CharacterStateType)j["player"]["state"]);
    character->setActionState((ActionState)j["player"]["action"]);
    character->setDirection((Direction)j["player"]["direction"]);

    // Load HUD
    hud = new HUD(level);
    hud->setScore(j["hud"]["score"]);
    hud->setCoins(j["hud"]["coins"]);
    hud->setLives(j["hud"]["lives"]);
    hud->setTime(j["hud"]["time"]);
}

void PlayState::spawnEnemy(){


    //Setup factory map
    enemyFactories[EnemyType::GOOMBA] = make_unique<GoomBaFactory>();
    enemyFactories[EnemyType::KOOPA] = make_unique<KoopaTroopaFactory>(EnemyType::KOOPA);
    enemyFactories[EnemyType::REDKOOPA] = make_unique<KoopaTroopaFactory>(EnemyType::REDKOOPA);
    enemyFactories[EnemyType::PIRANT_PLANT] = make_unique<PiranhaPlantFactory>();
    enemyFactories[EnemyType::BOWSER] = make_unique<BowserFactory>();
    enemyFactories[EnemyType::KOOPA_PARATROOPA] = make_unique<KoopaParatroopaFactory>();

    world[level]->setEnemySpawnCallback(
        [this](EnemyType type, Vector2 pos, MapTheme theme) {
            auto it = enemyFactories.find(type);
            if (it != enemyFactories.end()) {
                enemies.push_back(it->second->createEnemy(pos, theme));
            }
        }
    );

}
