#include "../headers/ConcreteTileBehavior.h"
#include "../headers/Map.h"
#include "raylib.h"
#include "../headers/Global.h"
#include "../headers/EffectManager.h"
#include "../headers/NormalState.h"
#include "../headers/FireState.h"
#include "../headers/SuperState.h"
#include "../headers/ItemManager.h"
#include "../headers/SoundManager.h"
#include "../headers/Singleton.h"

void BrickTileBehavior::onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {
    //if(mario is small ) -> ko the bi vo  
    // Nếu chưa có state → tạo mới
    //BOUNCE
    //if (!tileInstance) return;
    auto* brickState = dynamic_cast<BrickTileState*>(tileInstance->state);
    if (!brickState) {
        brickState = new BrickTileState();
        tileInstance->state = brickState;
        
    }

    CharacterState* currentState = character->GetCurrentState();
    ////bounce
    if(currentState == dynamic_cast<NormalState*>(currentState)){
        if (!brickState->isBouncing) {
            Singleton<SoundManager>::getInstance().play(SoundType::BUMP);
            brickState->isBouncing = true;
            brickState->bounceTimer.start(0.2);
        }

    }
    else if(currentState == dynamic_cast<SuperState*>(currentState) || currentState == dynamic_cast<FireState*>(currentState)){
        if (!brickState->hasBroken) {
            Singleton<SoundManager>::getInstance().play(SoundType::BRICK_BREAK);
            brickState->hasBroken = true;
            character->breakBrick();
        }

    }
    
    
} // bị vỡ ra -> add effect mảnh vỡ
void BrickTileBehavior::update(float dt, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {
    
    //if (!tileInstance) return;
    auto* brickState = dynamic_cast<BrickTileState*>(tileInstance->state);
    //if (!brickState || !brickState->isBouncing) return;
    if (!brickState) return;
   
    
    if (brickState->isBouncing) {
        brickState->bounceTimer.update(dt);
        float bounceHeight = 25;
        float offsetY = -bounceHeight * brickState->bounceTimer.getProgress();

        if (brickState->bounceTimer.getProgress() > 0.5) {
            offsetY = -bounceHeight * (1 - brickState->bounceTimer.getProgress());
        }
        //offsetY *= dt;
        map->updateTileInstancePosition(tileRow, tileCol, { 0, offsetY }, LayerType::PLATFORM);

        if (brickState->bounceTimer.isFinished()) {
            brickState->isBouncing = false;
            map->updateTileInstancePosition(tileRow, tileCol, { 0, 0 }, LayerType::PLATFORM); // reset vị trí
        }
    }

    if (brickState->hasBroken) {
        //EffectManager::get().spawnCoin(tileRow, tileCol);
        Tile tile = map->getTile(tileInstance->tileID);
        Singleton<EffectManager>::getInstance().spawnBrickBreak(tileRow, tileCol, tile.theme);
        brickState->hasBroken = false;
        map->removeTile(tileRow, tileCol);
    }

}

//QUESTION
void QuestionTileBehavior::onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance){
    auto* tileState = dynamic_cast<QuestionTileState*>(tileInstance->state);
    if (!tileState) {
        tileState = new QuestionTileState();
        tileInstance->state = tileState;
    }

    if(!tileState->isBouncing){
        tileState->isBouncing = true;
        tileState->bounceTimer.start(0.2f);
        //cout << tileRow << " - " << tileCol << endl;
        Vector2 startPos = {(float) tileCol * Map::TILE_SIZE, (float) tileRow * Map::TILE_SIZE};

        if(tileInstance->tileID  == 20 || tileInstance->tileID == 77 || tileInstance->tileID == 134 || tileInstance->tileID == 191){
           if(character->getCharacterStateType() == CharacterStateType::NormalState)
                Singleton<ItemManager>::getInstance().Spawn(ItemType::MUSHROOM, startPos);
            else {
                Singleton<ItemManager>::getInstance().Spawn(ItemType::FLOWER, startPos);
            }
            Singleton<SoundManager>::getInstance().play(SoundType::ITEMCOLLECT);

        }
        else if (tileInstance->tileID == 21 || tileInstance->tileID == 21 + 57 || tileInstance->tileID == 21 + 57 * 2 || tileInstance->tileID == 21 + 57 * 3 ){
            Singleton<EffectManager>::getInstance().spawnCoin(tileRow, tileCol);
            Singleton<SoundManager>::getInstance().play(SoundType::COIN);
            character->collectCoin();
        }
        else if(tileInstance->tileID == 50 || tileInstance->tileID == 50 + 57 || tileInstance->tileID == 50 + 57 * 2 || tileInstance->tileID == 50 + 57 * 3 ){
            Singleton<ItemManager>::getInstance().Spawn(ItemType::STAR, startPos);
            Singleton<SoundManager>::getInstance().play(SoundType::ITEMCOLLECT);
        }
        //spawn items
    }

}

void QuestionTileBehavior::update(float dt, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance){
    auto* tileState = dynamic_cast<QuestionTileState*>(tileInstance->state);
    if(!tileState) return;
    
    if (tileState->isBouncing) {
        tileState->bounceTimer.update(dt);
        float bounceHeight = 25;
        float offsetY = -bounceHeight * tileState->bounceTimer.getProgress();

        if (tileState->bounceTimer.getProgress() > 0.5) {
            offsetY = -bounceHeight * (1 - tileState->bounceTimer.getProgress());
        }
        //offsetY *= dt;
        map->updateTileInstancePosition(tileRow, tileCol, { 0, offsetY }, LayerType::PLATFORM);

        if (tileState->bounceTimer.isFinished()) {
            tileState->isBouncing = false;
            map->updateTileInstancePosition(tileRow, tileCol, { 0, 0 }, LayerType::PLATFORM); // reset vị trí
            int id =  map->getTileIDFromCoords(1 +(int) map->getTile(tileInstance->tileID).theme * 2 , 5 );
            map->setTile(tileRow, tileCol, id, static_cast<int>(LayerType::PLATFORM));
           // cout << 1;
        }
    }

}


