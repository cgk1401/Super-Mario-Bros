#include "../headers/ConcreteTileBehavior.h"
#include "../headers/Map.h"
#include "raylib.h"
#include "../headers/Global.h"
#include "../headers/EffectManager.h"

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


    ////bounce
    /*if (!brickState->isBouncing) {
        brickState->isBouncing = true;
        brickState->bounceTimer.start(0.3);
    }*/
    if (!brickState->hasBroken) {
        
        brickState->hasBroken = true;
    }

    
} // bị vỡ ra -> add effect mảnh vỡ
void BrickTileBehavior::update(float dt, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {
    
    //if (!tileInstance) return;
    auto* brickState = dynamic_cast<BrickTileState*>(tileInstance->state);
    //if (!brickState || !brickState->isBouncing) return;
    if (!brickState) return;
   
    
    /*
    if (brickState->isBouncing) {
        brickState->bounceTimer.update(dt);
        float bounceHeight = 15.0;
        float offsetY = -bounceHeight * brickState->bounceTimer.getProgress();

        if (brickState->bounceTimer.getProgress() > 0.5) {
            offsetY = -bounceHeight * (1 - brickState->bounceTimer.getProgress());
        }
        //offsetY *= dt;
        map->updateTileInstancePosition(tileRow, tileCol, { 0, offsetY });

        if (brickState->bounceTimer.isFinished()) {
            brickState->isBouncing = false;
            map->updateTileInstancePosition(tileRow, tileCol, { 0, 0 }); // reset vị trí
        }
    }
    */
     if (brickState->hasBroken) {
        EffectManager::get().spawnCoin(tileRow, tileCol);
        EffectManager::get().spawnBrickBreak(tileRow, tileCol);
        brickState->hasBroken = false;
        //map->removeTile(tileRow, tileCol);
    }

}


