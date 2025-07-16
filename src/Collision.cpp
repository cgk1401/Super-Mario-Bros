#include "../headers/Collision.h"
#include "../headers/Global.h"
#include "../headers/Character.h"
#include "../headers/Enemy.h"
#include "../headers/Map.h"
#include "../headers/Mushroom.h"
#include "../headers/Star.h"
#include "../headers/EffectManager.h"
#include <cmath>

void Collision::handlePlayerCollision(Character* player, Map* map) {
 
    player->currentState->isGround = false;

    Rectangle bound      = player->getBound();
    Rectangle footSensor = player->getFootSensor();

    if (player->position.x < 0) player->position.x = 0;

    int characterLeftTile = (int)(bound.x / Map::TILE_SIZE);
    int characterRightTile = (int)((bound.x + bound.width) / Map::TILE_SIZE);
    int characterTopTile = (int)(bound.y / Map::TILE_SIZE);
    int characterBottomTile = (int)((bound.y + bound.height) / Map::TILE_SIZE);


    int startCol = max(0, characterLeftTile - 1);
    int endCol = min(map->columns - 1, characterRightTile + 1);
    int startRow = max(0, characterTopTile - 1);
    int endRow = min(map->rows - 1, characterBottomTile + 1);

    for (int x = endRow - 1 < 0 ? 0 : endRow - 1; x <= endRow; x++) {
        for (int y = startCol; y <= endCol; y++) {
            Tile tile = map->getTile(x, y);
            MapTileInstance* tileInstance = map->getMapTileInstance(x, y);
            Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

            if (CheckCollisionRecs(tileRect, footSensor) && tile.behavior->isSolid()) {
                player->position.y = tileRect.y - bound.height - 0.5f;
                player->velocity.y = 0;

                player->currentState->isGround = true;
                player->currentState->isJumpingUp = false;
                tile.behavior->onFootCollision(player, x, y, map, tileInstance);
            }
        }
    }
      endRow = endRow - 1 < startRow ? startRow : endRow - 1;
    for (int x = startRow; x <= endRow; x++) {
        for (int y = startCol; y <= endCol; y++) {
            Tile tile = map->getTile(x, y);

            MapTileInstance* tileInstance = map->getMapTileInstance(x, y);
            Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

            if (CheckCollisionRecs(bound, tileRect)) {
                if (tile.behavior->isSolid()) {
                    float overlapX = fmin(bound.x + bound.width, tileRect.x + tileRect.width) - fmax(bound.x, tileRect.x);
                    float overlapY = fmin(bound.y + bound.height, tileRect.y + tileRect.height) - fmax(bound.y, tileRect.y);
                    //cout<< overlapX << " - " << overlapY << endl;
                    if (overlapX > 0 && overlapY > 0) {
                        if (overlapY < overlapX) { // trên dưới của tile
                            if (player->velocity.y < 0) { // chạm đầu
                                player->position.y = tileRect.y + tileRect.height;
                                player->velocity.y = 0;
                                player->currentState->isJumpingUp = false;
                                tile.behavior->onHeadCollision(player, x, y, map, tileInstance);
                            }

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

    Rectangle bound = e->bound;
    float width = bound.width;
    float height = 2;
    Rectangle footSensor = {
            bound.x,
            bound.y + bound.height - height / 2,
            width,
            height
    };

    int characterLeftTile = (int)(bound.x / Map::TILE_SIZE);
    int characterRightTile = (int)((bound.x + bound.width) / Map::TILE_SIZE);
    int characterTopTile = (int)(bound.y / Map::TILE_SIZE);
    int characterBottomTile = (int)((bound.y + bound.height) / Map::TILE_SIZE);


    int startCol = max(0, characterLeftTile - 1);
    int endCol = min(map->columns - 1, characterRightTile + 1);
    int startRow = max(0, characterTopTile - 1);
    int endRow = min(map->rows - 1, characterBottomTile + 1);

    for (int x = endRow - 1 < 0 ? 0 : endRow - 1; x <= endRow; x++) {
        for (int y = startCol; y <= endCol; y++) {
            Tile tile = map->getTile(x, y);
            MapTileInstance* tileInstance = map->getMapTileInstance(x, y);
            Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

            if (CheckCollisionRecs(tileRect, footSensor) && tile.behavior->isSolid()) {
                e->position.y = tileRect.y - bound.height;
                e->velocity.y = 0;

                e->onGround = true;
            }
        }
    }

    endRow = endRow - 1 < startRow ? startRow : endRow - 1;

    for (int x = startRow; x <= endRow; x++) {
        for (int y = startCol; y <= endCol; y++) {
            Tile tile = map->getTile(x, y);
            Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

            if (CheckCollisionRecs(bound, tileRect)) {
                if (tile.behavior->isSolid()) {
                    float overlapX = fmin(bound.x + bound.width, tileRect.x + tileRect.width) - fmax(bound.x, tileRect.x);
                    float overlapY = fmin(bound.y + bound.height, tileRect.y + tileRect.height) - fmax(bound.y, tileRect.y);
                    //cout<< overlapX << " - " << overlapY << endl;
                    if (overlapX > 0 && overlapY > 0) {
                        if (overlapY < overlapX) { // trên dưới của tile
                            if (e->velocity.y < 0) { // chạm đầu
                                e->position.y = tileRect.y + tileRect.height;
                                e->velocity.y = 0;
                            }

                        }
                        else { // 2 bên của tile 
                            if (e->velocity.x > 0) { // đang đi sang phải,  đụng bên trái tile
                                e->position.x -= overlapX;
                                e->changeDirection(Direction::Left);
                            }
                            else if (e->velocity.x < 0) { // đang đi sang trái, đụng bên phải tile
                                e->position.x += overlapX;
                                e->changeDirection(Direction::Right);
                            }
                            e->velocity.x = 0;
                        }
                        bound = e->bound;
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
    float width = bound.width ;
    float height = 2;
    Rectangle footSensor = {
            bound.x,
            bound.y + bound.height - height / 2,
            width,
            height
    };

    int characterLeftTile = (int)(bound.x / Map::TILE_SIZE);
    int characterRightTile = (int)((bound.x + bound.width) / Map::TILE_SIZE);
    int characterTopTile = (int)(bound.y / Map::TILE_SIZE);
    int characterBottomTile = (int)((bound.y + bound.height) / Map::TILE_SIZE);


    int startCol = max(0, characterLeftTile - 1);
    int endCol = min(map->columns - 1, characterRightTile + 1);
    int startRow = max(0, characterTopTile - 1);
    int endRow = min(map->rows - 1, characterBottomTile + 1);

    for (int x = endRow - 1 < 0 ? 0 : endRow - 1; x <= endRow; x++) {
        for (int y = startCol; y <= endCol; y++) {
            Tile tile = map->getTile(x, y);
            Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

            if (CheckCollisionRecs(tileRect, footSensor) && tile.behavior->isSolid()) {
                mushroom->position.y = tileRect.y - bound.height - 1;
                mushroom->velocity.y = 0;

                mushroom->onGround = true;
            }
        }
    }

    endRow = endRow - 1 < startRow ? startRow : endRow - 1;
    for (int x = startRow; x <= endRow; x++) {
        for (int y = startCol; y <= endCol; y++) {
            Tile tile = map->getTile(x, y);
            Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

            if (CheckCollisionRecs(bound, tileRect)) {
                if (tile.behavior->isSolid()) {
                    float overlapX = fmin(bound.x + bound.width, tileRect.x + tileRect.width) - fmax(bound.x, tileRect.x);
                    float overlapY = fmin(bound.y + bound.height, tileRect.y + tileRect.height) - fmax(bound.y, tileRect.y);
                    //cout<< overlapX << " - " << overlapY << endl;
                    if (overlapX > 0 && overlapY > 0) {
                        if (overlapY < overlapX) { // trên dưới của tile
                            if (mushroom->velocity.y < 0) { // chạm đầu
                                mushroom->position.y = tileRect.y + tileRect.height;
                                mushroom->velocity.y = 0;
                            }

                        }
                        else { // 2 bên của tile 
                            cout << x << " - " << y << endl;
                            if (mushroom->velocity.x > 0) { // đang đi sang phải,  đụng bên trái tile
                                mushroom->position.x -= overlapX;
                                mushroom->changeDirection(Direction::Left);
                            }
                            else if (mushroom->velocity.x < 0) { // đang đi sang trái, đụng bên phải tile
                                mushroom->position.x += overlapX;
                                mushroom->changeDirection(Direction::Right);
                            }
                            mushroom->velocity.x = 0;
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
    float width = bound.width;
    float height = 2;
    Rectangle footSensor = {
            bound.x,
            bound.y + bound.height - height / 2,
            width,
            height
    };

    int characterLeftTile = (int)(bound.x / Map::TILE_SIZE);
    int characterRightTile = (int)((bound.x + bound.width) / Map::TILE_SIZE);
    int characterTopTile = (int)(bound.y / Map::TILE_SIZE);
    int characterBottomTile = (int)((bound.y + bound.height) / Map::TILE_SIZE);


    int startCol = max(0, characterLeftTile - 1);
    int endCol = min(map->columns - 1, characterRightTile + 1);
    int startRow = max(0, characterTopTile - 1);
    int endRow = min(map->rows - 1, characterBottomTile + 1);

    for (int x = endRow - 1 < 0 ? 0 : endRow - 1; x <= endRow; x++) {
        for (int y = startCol; y <= endCol; y++) {
            Tile tile = map->getTile(x, y);
            Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

            if (CheckCollisionRecs(tileRect, footSensor) && tile.behavior->isSolid()) {
                star->position.y = tileRect.y - bound.height - 1;
                star->velocity.y = 0;

                star->onGround = true;
            }
        }
    }

    endRow = endRow - 1 < startRow ? startRow : endRow - 1;
    for (int x = startRow; x <= endRow; x++) {
        for (int y = startCol; y <= endCol; y++) {
            Tile tile = map->getTile(x, y);
            Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

            if (CheckCollisionRecs(bound, tileRect)) {
                if (tile.behavior->isSolid()) {
                    float overlapX = fmin(bound.x + bound.width, tileRect.x + tileRect.width) - fmax(bound.x, tileRect.x);
                    float overlapY = fmin(bound.y + bound.height, tileRect.y + tileRect.height) - fmax(bound.y, tileRect.y);
                    //cout<< overlapX << " - " << overlapY << endl;
                    if (overlapX > 0 && overlapY > 0) {
                        if (overlapY < overlapX) { // trên dưới của tile
                            if (star->velocity.y < 0) { // chạm đầu
                                star->position.y = tileRect.y + tileRect.height;
                                star->velocity.y = 0;
                            }

                        }
                        else { // 2 bên của tile 
                            cout << x << " - " << y << endl;
                            if (star->velocity.x > 0) { // đang đi sang phải,  đụng bên trái tile
                                star->position.x -= overlapX;
                                star->direction = Direction::Left;
                            }
                            else if (star->velocity.x < 0) { // đang đi sang trái, đụng bên phải tile
                                star->position.x += overlapX;
                                star->direction = Direction::Right;
                            }
                            star->velocity.x = 0;
                        }
                        bound = star->getBound();
                    }
                }
            }

        }
    }
}


void Collision::handleFireBallCollisionMap(FireBall* fireball , Map* map) {
    
    fireball->onGround = false;
    Rectangle bound = fireball->getBound();

    int left = (int)(bound.x / Map::TILE_SIZE);
    int right = (int)((bound.x + bound.width) / Map::TILE_SIZE);
    int top = (int)(bound.y / Map::TILE_SIZE);
    int bottom = (int)((bound.y + bound.height) / Map::TILE_SIZE);

    int fireballtCol = max(0, left - 1);
    int endCol = min(map->columns - 1, right + 1);
    int fireballtRow = max(0, top - 1);
    int endRow = min(map->rows - 1, bottom + 1);

    for (int x = fireballtRow; x <= endRow; x++) {
        for (int y = fireballtCol; y <= endCol; y++) {
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
                    
                        if (fireball->velocity.y > 0) {
                            fireball->position.y -= overlapY;
                            fireball->velocity.y = fireball->BOUNCE_VELOCITY; // Bật lên
                            fireball->onGround = true;
                        }
                        else if (fireball->velocity.y < 0) {
                            fireball->position.y += overlapY;
                            fireball->velocity.y = 0;
                            fireball->Deactivate();
                            Singleton<EffectManager>::getInstance().explosionEffect(fireball->position);
                        }
                    }
                    else {
                        if (fireball->velocity.x > 0) {
                            fireball->position.x -= overlapX;
                            fireball->Deactivate();
                            Singleton<EffectManager>::getInstance().explosionEffect(fireball->position);
                        }
                        else {
                            fireball->position.x += overlapX;
                            fireball->Deactivate();
                            Singleton<EffectManager>::getInstance().explosionEffect(fireball->position);
                        }
                        //fireball->velocity.x *= -1; 
                    }

                    bound = fireball->getBound();
                }
            }
        }
    }
}


