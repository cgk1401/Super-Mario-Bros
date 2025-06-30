#include "../headers/Collision.h"
#include "../headers/Global.h"
#include "../headers/Character.h"
#include "../headers/Map.h"

Collision* Collision::instance = nullptr;


Collision::~Collision() {
    delete instance;
}

void Collision::handlePlayerCollision(Character* mario, Map* map){
    Rectangle currentFrame = mario->animation[mario->currentstate].getcurrentframe();
    mario->bound = { mario->position.x, mario->position.y, currentFrame.width * mario->scale, currentFrame.height * mario->scale };

    mario->onGround = false;

    if (mario->position.x < 0) mario->position.x = 0;
    int characterLeftTile = (int)((mario->bound.x + mario->bound.width / 2) / Map::TILE_SIZE);
    int characterRightTile = (int)((mario->bound.x + mario->bound.width) / Map::TILE_SIZE);
    int characterTopTile = (int)(mario->bound.y / Map::TILE_SIZE);
    int characterBottomTile = (int)((mario->bound.y + mario->bound.height) / Map::TILE_SIZE);

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
            //tile.behavior->update(GetFrameTime(), x, y, map, tileInstance);
          
            if (CheckCollisionRecs(mario->bound, tileRect)) {
                if (tile.behavior->isSolid()) {
                    float overlapX = fmin(mario->bound.x + mario->bound.width, tileRect.x + tileRect.width) - fmax(mario->bound.x, tileRect.x);
                    float overlapY = fmin(mario->bound.y + mario->bound.height, tileRect.y + tileRect.height) - fmax(mario->bound.y, tileRect.y);

                    if (overlapX > 0 && overlapY > 0) {
                        if (overlapY < overlapX) { // trên dưới của tile
                            if (mario->velocity.y > 0) { // is falling
                                mario->position.y -= overlapY;
                                mario->velocity.y = 0;
                                mario->onGround = true;
                                mario->isJumpingUp = false;
                                tile.behavior->onFootCollision(mario, x, y, map, tileInstance);
                            }
                            else if (mario->velocity.y < 0) { // chạm đầu
                                mario->position.y += overlapY;
                                mario->velocity.y = 0;
                                mario->isJumpingUp = false;
                                tile.behavior->onHeadCollision(mario, x, y, map, tileInstance);
                            }

                            
                            //position.y = floor(position.y);
                        }
                        else { // 2 bên của tile 
                            if (mario->velocity.x > 0) { // đang đi sang phải,  đụng bên trái tile
                                mario->position.x -= overlapX;
                            }
                            else if (mario->velocity.x < 0) { // đang đi sang trái, đụng bên phải tile
                                mario->position.x += overlapX;
                            }
                            mario->velocity.x = 0;
                            tile.behavior->onGeneralCollision(mario, x, y, map, tileInstance);
                        }
                        mario->bound.x = mario->position.x;
                        mario->bound.y = mario->position.y;
                    }
                }
            }
        }
    }
}
void Collision::handleEnemyCollision(vector<Character*> enemies, Map* map){

    for(auto& e: enemies){
        Rectangle currentFrame = e->animation[e->currentstate].getcurrentframe();
        e->bound = { e->position.x, e->position.y, currentFrame.width * e->scale, currentFrame.height * e->scale };

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
                                    e->isJumpingUp = false;
                                }
                                else if (e->velocity.y < 0) { // chạm đầu
                                    e->position.y += overlapY;
                                    e->velocity.y = 0;
                                    e->isJumpingUp = false;
                                 
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
}
