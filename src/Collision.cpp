#include "../headers/Collision.h"
#include "../headers/Global.h"
#include "../headers/Character.h"
#include "../headers/Enemy.h"
#include "../headers/Map.h"
#include "../headers/Mushroom.h"
#include "../headers/Star.h"
#include "../headers/EffectManager.h"
#include "../headers/GoomBa.h"
#include "../headers/KoopaTroopa.h"
#include "../headers/ConcreteTileBehavior.h"
#include <cmath>


void Collision::handleMapCollision(GameObject* object, Map* map){
    if(object->interactWithMap == false) return;

    object->onGround = false;

    Rectangle bound      = object->getBound();

    float eps = 0.1f;
    float width = bound.width * (1- eps * 2);
    float height = 1;
    Rectangle footSensor = {
            bound.x + bound.width * eps,
            bound.y + bound.height + height,
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

    vector<LayerType> layerTypes = {LayerType::PLATFORM};

    for(auto& layerType: layerTypes){
        for (int x = endRow - 1 < 0 ? 0 : endRow - 1; x <= endRow; x++) {
            for (int y = startCol; y <= endCol; y++) {
                Tile tile = map->getTile(x, y, layerType);
                MapTileInstance* tileInstance = map->getMapTileInstance(x, y, layerType);
                Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

                if (CheckCollisionRecs(tileRect, footSensor) && tile.behavior->isSolid()) {
                    object->position.y = tileRect.y - bound.height;
                    object->velocity.y = 0;
                    object->onGround = true;
                    object->onFootCollision(tile, x, y, map, tileInstance);
                }
            }
        }
        for (int x = startRow; x <= endRow; x++) {
            for (int y = startCol; y <= endCol; y++) {
                Tile tile = map->getTile(x, y, layerType);

                MapTileInstance* tileInstance = map->getMapTileInstance(x, y, layerType);
                Rectangle tileRect = { (float)(y * Map::TILE_SIZE), (float)(x * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };

                if (CheckCollisionRecs(bound, tileRect)) {
                    if(object->getObjectType() == ObjectType::CHARACTER ){
                        if (tile.type == TileType::FINISHING_POLE ) {
                            Character* character = dynamic_cast<Character*>(object);
                            if(character->getCurrentAction()== ActionState::FlagpoleHold || character->isControlled == true) return;
                                character->velocity = {0,0};
                                character->position.x = y * Map::TILE_SIZE;
                                character->notify(EventType::FLAG_POLE, &tileRect);
                            return;
                        }
                        else if(tile.type == TileType::HORIZONTAL_PIPE){
                             Character* character = dynamic_cast<Character*>(object);
                            if(character->isControlled == true) return;
                             Direction collideDirection = getCollisionDirection(bound, tileRect);
                             if(collideDirection == Direction::Right){
                                character->notify(EventType::PIPE_ENTER, &tileRect);
                             }
                             return;
                        }
                    }
                    if (tile.behavior->isSolid()) {
                        float overlapX = fmin(bound.x + bound.width, tileRect.x + tileRect.width) - fmax(bound.x, tileRect.x);
                        float overlapY = fmin(bound.y + bound.height, tileRect.y + tileRect.height) - fmax(bound.y, tileRect.y);
                        if (overlapX > 0 && overlapY > 0) {
                            Direction collideDirection = getCollisionDirection(bound, tileRect);
                            if(collideDirection == Direction::Top){
                                object->position.y = tileRect.y + tileRect.height;
                                object->velocity.y = 0;
                                object->onHeadCollision(tile, x, y, map, tileInstance);
                            }
                            else if(collideDirection == Direction::Left){
                                object->position.x += overlapX;
                                object->velocity.x = 0;
                                object->onGeneralCollision(Direction::Left, tile, x, y, map, tileInstance);
                            }
                            else if(collideDirection == Direction::Right){
                                object->position.x -= overlapX;
                                object->velocity.x = 0;
                                object->onGeneralCollision(Direction::Right, tile, x, y, map, tileInstance);
                            }
                            bound = object->getBound();
                        }
                    }
                }
            
            }
        }
    }
}


void Collision::handleObjectsCollision(GameObject* a, GameObject* b){
    if(CheckCollisionRecs(a->getBound(), b->getBound())){
        a->onCollideWith(b);
        b->onCollideWith(a);
    }
}

void Collision::handleMultipleObjectCollisions(vector<GameObject*>& objects) {
    for (size_t i = 0; i < objects.size(); ++i) {
        for (size_t j = i + 1; j < objects.size(); ++j) {
            handleObjectsCollision(objects[i], objects[j]);
        }
    }
}
