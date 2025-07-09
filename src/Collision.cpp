#include "../headers/Collision.h"
#include "../headers/Global.h"
#include "../headers/Character.h"
#include "../headers/Enemy.h"
#include "../headers/Map.h"

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

    if (e->position.x < 0) e->position.x = 0;
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
