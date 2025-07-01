#include "../headers/EffectManager.h"
#include <algorithm>
#include "../headers/Map.h"

EffectManager* EffectManager::instance = nullptr;

EffectManager::EffectManager(){
    texture = LoadTexture("../assets/Item/Items Objects and NPCs.png");
    vector<Rectangle> brickFrames;
    for(int i = 0; i < 2; i++){
        brickFrames.push_back(Rectangle{(float)(181 + i * 10), 26, 7, 7});
    }

    brickExplosionAnim.frame = brickFrames;
    brickExplosionAnim.durationtime = 0.08f;
   
}

void EffectManager::spawnBrickBreak(int row, int col){
    float x =(float) col * Map::TILE_SIZE;
    float y =(float) row * Map::TILE_SIZE;

    Vector2 spawnPos = { x + Map::TILE_SIZE / 2 - 8, y + Map::TILE_SIZE / 2 - 8 }; // căn giữa tile
    
    brickEffects.emplace_back(new BrickBreakEffect(spawnPos, brickExplosionAnim));
    
}

void EffectManager::update(float dt){
    for(auto& b : brickEffects){
        b->update(dt);
    }
    //xoa nhung effect da hoan thanh(vuot qua sreenheight)
    erase_if(brickEffects, [](BaseEffect* e) {
        return e->isFinished();
        });
}

void EffectManager::draw(){
    for(auto& b : brickEffects){
        b->draw(texture);
    }
}

bool EffectManager::isFinished() const {
   
    for (auto& b : brickEffects) {
        if (!b->isFinished()) return false;
    }
    return true;
}