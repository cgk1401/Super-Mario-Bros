#include "../headers/Collision.h"
#include "../headers/Global.h"
#include "../headers/Character.h"
#include "../headers/Enemy.h"
#include "../headers/Map.h"
#include "../headers/Mushroom.h"
#include "../headers/Star.h"
#include <cmath>
void Collision::handlePlayerCollision(Character* player, Map* map) {
    player->currentState->isGround = false;

    Rectangle bound = player->getBound();

    if (player->position.x < 0) player->position.x = 0;

    int characterLeftTile   = (int)(bound.x / Map::TILE_SIZE);
    int characterRightTile  = (int)((bound.x + bound.width) / Map::TILE_SIZE);
    int characterTopTile    = (int)(bound.y / Map::TILE_SIZE);
    int characterBottomTile = (int)((bound.y + bound.height) / Map::TILE_SIZE);

    int startCol = max(0, characterLeftTile - 2);
    int endCol   = min(map->columns - 1, characterRightTile + 2);
    int startRow = max(0, characterTopTile - 2);
    int endRow   = min(map->rows - 1, characterBottomTile + 2);

    for (int x = startRow; x <= endRow; x++) {
       for (int y = startCol; y <= endCol; y++) {
           Tile tile = map->getTile(x, y);

           MapTileInstance* tileInstance = map->getMapTileInstance(x, y);
           Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

           //if (!tileInstance || tileInstance->tileID == 0) continue;

           if (CheckCollisionRecs(bound, tileRect)) {
               if (tile.behavior->isSolid()) {
                   float overlapX = fmin(bound.x + bound.width, tileRect.x + tileRect.width) - fmax(bound.x, tileRect.x);
                   float overlapY = fmin(bound.y + bound.height, tileRect.y + tileRect.height) - fmax(bound.y, tileRect.y);

                   if (overlapX > 0 && overlapY > 0) {
                       if (overlapY < overlapX) { // trên dưới của tile
                           if (player->velocity.y > 0) { // is falling
                               player->position.y -= overlapY;
                               player->velocity.y = 0;
                               player->currentState->isGround = true;
                               player->currentState->isJumpingUp = false;
                               tile.behavior->onFootCollision(player, x, y, map, tileInstance);
                           }
                           else if (player->velocity.y < 0) { // chạm đầu
                               player->position.y += overlapY;
                               player->velocity.y = 0;
                               player->currentState->isJumpingUp = false;
                               tile.behavior->onHeadCollision(player, x, y, map, tileInstance);
                           }

                           
                           //position.y = floor(position.y);
                       }
                       else { // 2 bên của tile 
                           if (player->velocity.x > 0) { // đang đi sang phải,  đụng bên trái tile
                               player->position.x -= overlapX;
                           }
                           else if (player->velocity.x < 0) { // đang đi sang trái, đụng bên phải tile
                               player->position.x += overlapX;
                           }
                           player->velocity.x = 0;
                           tile.behavior->onGeneralCollision(player, x, y, map, tileInstance);
                       }
                       bound = player->getBound();
                   }
               }
           }
       }
   }
}

void Collision::handleEnemyCollision(Enemy* e, Map* map){
    e->onGround = false;

    //if (e->position.x < 0) e->position.x = 0;
    int characterLeftTile = (int)(e->bound.x / Map::TILE_SIZE);
    int characterRightTile = (int)((e->bound.x + e->bound.width) / Map::TILE_SIZE);
    int characterTopTile = (int)(e->bound.y / Map::TILE_SIZE);
    int characterBottomTile = (int)((e->bound.y + e->bound.height) / Map::TILE_SIZE);

    int startCol = max(0, characterLeftTile - 1);
    int endCol = min(map->columns - 1, characterRightTile + 1);
    int startRow = max(0, characterTopTile - 1);
    int endRow = min(map->rows - 1, characterBottomTile + 1);

    for (int x = startRow; x <= endRow; x++) {
        for (int y = startCol; y <= endCol; y++) {
            Tile tile = map->getTile(x, y);

            MapTileInstance* tileInstance = map->getMapTileInstance(x, y);
            Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

            //if (!tileInstance || tileInstance->tileID == 0) continue;

            if (CheckCollisionRecs(e->bound, tileRect)) {
                if (tile.behavior->isSolid()) {
                    float overlapX = fmin(e->bound.x + e->bound.width, tileRect.x + tileRect.width) - fmax(e->bound.x, tileRect.x);
                    float overlapY = fmin(e->bound.y + e->bound.height, tileRect.y + tileRect.height) - fmax(e->bound.y, tileRect.y);

                    if (overlapX > 0 && overlapY > 0) {
                        if (overlapY < overlapX) { // trên dưới của tile
                            if (e->velocity.y > 0) { // is falling
                                e->position.y -= overlapY;
                                e->velocity.y = 0;
                                e->onGround = true;
                                
                            }
                            else if (e->velocity.y < 0) { // chạm đầu
                                e->position.y += overlapY;
                                e->velocity.y = 0;
                                
                            }

                            
                            //position.y = floor(position.y);
                        }
                        else { // 2 bên của tile 
                            if (e->velocity.x > 0) { // đang đi sang phải,  đụng bên trái tile
                                e->position.x -= overlapX;
                            }
                            else if (e->velocity.x < 0) { // đang đi sang trái, đụng bên phải tile
                                e->position.x += overlapX;
                            }
                            e->velocity.x = 0;
                            
                        }
                        e->bound.x = e->position.x;
                        e->bound.y = e->position.y;
                    }
                }
            }
        }
    }
    
}


void Collision::handleMushroomCollisionMap(Mushroom* mushroom, Map* map){
    if(mushroom->isRunning() == false) return;
    mushroom->onGround = false;

    Rectangle bound = mushroom->getBound();
    int mushroomLeftTile   = (int)(bound.x / Map::TILE_SIZE);
    int mushroomRightTile  = (int)((bound.x + bound.width) / Map::TILE_SIZE);
    int mushroomTopTile    = (int)(bound.y / Map::TILE_SIZE);
    int mushroomBottomTile = (int)((bound.y + bound.height) / Map::TILE_SIZE);

    int startCol = max(0, mushroomLeftTile - 1);
    int endCol   = min(map->columns - 1, mushroomRightTile + 1);
    int startRow = max(0, mushroomTopTile - 1);
    int endRow   = min(map->rows - 1, mushroomBottomTile + 1);

    for (int x = startRow; x <= endRow; x++) {
       for (int y = startCol; y <= endCol; y++) {
           Tile tile = map->getTile(x, y);

           //MapTileInstance* tileInstance = map->getMapTileInstance(x, y);
           Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

           //if (!tileInstance || tileInstance->tileID == 0) continue;

           if (CheckCollisionRecs(bound, tileRect)) {
               if (tile.behavior->isSolid()) {
                   float overlapX = fmin(bound.x + bound.width, tileRect.x + tileRect.width) - fmax(bound.x, tileRect.x);
                   float overlapY = fmin(bound.y + bound.height, tileRect.y + tileRect.height) - fmax(bound.y, tileRect.y);

                   if (overlapX > 0 && overlapY > 0) {
                       if (overlapY < overlapX) { // trên dưới của tile
                           if (mushroom->velocity.y > 0) { // is falling
                               mushroom->position.y -= overlapY;
                               mushroom->velocity.y = 0;
                               mushroom->onGround = true;
                               
                           }
                           else if (mushroom->velocity.y < 0) { // chạm đầu
                               mushroom->position.y += overlapY;
                               mushroom->velocity.y = 0;
                               
                               //tile.behavior->onHeadCollision(mushroom, x, y, map, tileInstance);
                           }

                           
                           //position.y = floor(position.y);
                       }
                       else { // 2 bên của tile 
                           if (mushroom->velocity.x > 0) { // đang đi sang phải,  đụng bên trái tile
                               mushroom->position.x -= overlapX;
                               mushroom->changeDirection(Direction::Left);
                           }
                           else if (mushroom->velocity.x < 0) { // đang đi sang trái, đụng bên phải tile
                               mushroom->position.x += overlapX;
                               mushroom->changeDirection(Direction::Right);
                           }
                           mushroom->velocity.x = 0;
                           //tile.behavior->onGeneralCollision(mushroom, x, y, map, tileInstance);
                       }
                       bound = mushroom->getBound();
                   }
               }
           }
       }
   }
}

void Collision::handleStarCollision(Star* star, Map* map) {
    if (!star->isRunning()) return;

    star->onGround = false;
    Rectangle bound = star->getBound();

    int left   = (int)(bound.x / Map::TILE_SIZE);
    int right  = (int)((bound.x + bound.width) / Map::TILE_SIZE);
    int top    = (int)(bound.y / Map::TILE_SIZE);
    int bottom = (int)((bound.y + bound.height) / Map::TILE_SIZE);

    int startCol = max(0, left - 1);
    int endCol   = min(map->columns - 1, right + 1);
    int startRow = max(0, top - 1);
    int endRow   = min(map->rows - 1, bottom + 1);

    for (int x = startRow; x <= endRow; x++) {
        for (int y = startCol; y <= endCol; y++) {
            Tile tile = map->getTile(x, y);
            if (!tile.behavior->isSolid()) continue;

            Rectangle tileRect = {
                (float)(y * Map::TILE_SIZE),
                (float)(x * Map::TILE_SIZE),
                (float)Map::TILE_SIZE,
                (float)Map::TILE_SIZE
            };

            if (CheckCollisionRecs(bound, tileRect)) {
                float overlapX = fmin(bound.x + bound.width, tileRect.x + tileRect.width) - fmax(bound.x, tileRect.x);
                float overlapY = fmin(bound.y + bound.height, tileRect.y + tileRect.height) - fmax(bound.y, tileRect.y);

                if (overlapX > 0 && overlapY > 0) {
                    if (overlapY < overlapX) {
                        // Va chạm dọc
                        if (star->velocity.y > 0) {
                            star->position.y -= overlapY;
                            star->velocity.y = star->BOUNCE_FORCE; // Bật lên
                            star->onGround = true;
                        }
                        else if (star->velocity.y < 0) {
                            star->position.y += overlapY;
                            star->velocity.y = 0;
                        }
                    } else {
                        if (star->velocity.x > 0) {
                            star->position.x -= overlapX;
                            star->direction = Direction::Left;
                        } else {
                            star->position.x += overlapX;
                            star->direction = Direction::Right;
                        }
                        //star->velocity.x *= -1; 
                    }

                    bound = star->getBound();
                }
            }
        }
    }
}
