#include "../headers/EffectManager.h"
#include "../headers/CoinCollectEffect.h"
#include <algorithm>
#include "../headers/Map.h"
#include "../headers/TextureManager.h"

EffectManager* EffectManager::instance = nullptr;

EffectManager::EffectManager(){
    texture = TextureManager::get().load(TextureType::ITEM);

    //BRICK BREAK
    vector<Rectangle> brickFrames;
    for(int i = 0; i < 2; i++){
        brickFrames.push_back(Rectangle{(float)(180 + i * 10), 26, 8, 8});
    }

    brickExplosionAnim.frame = brickFrames;
    brickExplosionAnim.durationtime = 0.08f;
   
   //COIN COLLECT
    vector<Rectangle> coinFrames;
    for(int i = 0; i < 4; i++){
        coinFrames.push_back(Rectangle{(float)(180 + i * 10), 36, 8, 16});
    }

    coinCollectAnim.frame = coinFrames;
    coinCollectAnim.durationtime = 0.07;
}

void EffectManager::spawnBrickBreak(int row, int col){
    float x =(float) col * Map::TILE_SIZE;
    float y =(float) row * Map::TILE_SIZE;

    Vector2 spawnPos = { x + Map::TILE_SIZE / 2 - 8, y + Map::TILE_SIZE / 2 - 8 }; // căn giữa tile
    
    effects.emplace_back(new BrickBreakEffect(spawnPos, brickExplosionAnim));
    
}

void EffectManager::spawnCoin(int row, int col){
     float x =(float) col * Map::TILE_SIZE;
    float y =(float) row * Map::TILE_SIZE;

    Vector2 spawnPos = { x + Map::TILE_SIZE / 2 - 8, y};
    
    effects.emplace_back(new CoinCollectEffect(spawnPos, coinCollectAnim));
}

void EffectManager::update(float dt){
    for(auto& b : effects){
        b->update(dt);
    }
    //xoa nhung effect da hoan thanh
    erase_if(effects, [](BaseEffect* e) {
        return e->isFinished();
        });
}

void EffectManager::draw(){
    for(auto& b : effects){
        b->draw(texture);
    }
}
