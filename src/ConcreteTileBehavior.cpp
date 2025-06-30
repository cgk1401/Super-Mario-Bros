#include "../headers/ConcreteTileBehavior.h"
#include "../headers/Map.h"
#include "raylib.h"
#include "../headers/Global.h"

void BrickTileBehavior::onHeadCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {
    //if(mario is small ) -> ko the bi vo  
    // Nếu chưa có state → tạo mới
    auto* brickState = dynamic_cast<BrickTileState*>(tileInstance->state);
    if (!brickState) {
        brickState = new BrickTileState();
        tileInstance->state = brickState;
    }


    // Nếu đang không bounce → bắt đầu bounce
    if (!brickState->isBouncing) {
        brickState->isBouncing = true;
        brickState->bounceTimer.start(0.3);
    }
    
} // bị vỡ ra -> add effect mảnh vỡ
void BrickTileBehavior::onFootCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {} // đứng lên thì ko sao -> giống solid -> dùng lại SolidTileBehavior::onFootCollision(..)
void BrickTileBehavior::onGeneralCollision(Character* character, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {} // tương tự

void BrickTileBehavior::update(float dt, int tileRow, int tileCol, Map* map, MapTileInstance* tileInstance) {
    auto* brickState = dynamic_cast<BrickTileState*>(tileInstance->state);
    if (!brickState || !brickState->isBouncing) return;

    brickState->bounceTimer.update(dt);

    float bounceHeight = 15.0; 
    float offsetY = -bounceHeight * brickState->bounceTimer.getProgress();

    if (brickState->bounceTimer.getProgress() > 0.5) {
        offsetY = -bounceHeight * (1-brickState->bounceTimer.getProgress());
    }
    //offsetY *= dt;
    map->updateTileInstancePosition(tileRow, tileCol, { 0, offsetY });

    if (brickState->bounceTimer.isFinished()) {
        brickState->isBouncing = false;
        map->updateTileInstancePosition(tileRow, tileCol, { 0, 0 }); // reset vị trí
    }
}


