#include "../headers/Character.h"
#include "../headers/Map.h"
#include <iostream>
using namespace std;


Character::Character() : gravity(1500), velocity({ 0, 0 }) {
	scale = 1;
	bound = {};
	onGround = false;
	isJumpingUp = false;
    
}

/*
Character::~Character() {
	//UnloadTexture(texture);
	//animation.clear();
}
*/

Vector2 Character::getPos() {
	return position;
}

void Character::handleCollision(Map* map){
    Rectangle currentFrame = animation[currentstate].getcurrentframe();
    bound = { position.x, position.y, currentFrame.width * scale, currentFrame.height * scale };

    onGround = false;

    if (position.x < 0) position.x = 0;
    int characterLeftTile = (int)(bound.x / Map::side);
    int characterRightTile = (int)((bound.x + bound.width) / Map::side);
    int characterTopTile = (int)(bound.y / Map::side);
    int characterBottomTile = (int)((bound.y + bound.height) / Map::side);

    int startCol = max(0, characterLeftTile - 1);
    int endCol = min(map->columns - 1, characterRightTile + 1);
    int startRow = max(0, characterTopTile - 1);
    int endRow = min(map->rows - 1, characterBottomTile + 1);

    for (int x = startRow; x <= endRow; x++) {
        for (int y = startCol; y <= endCol; y++) {
            Tile tile = map->getTile(x, y);

            MapTileInstance* tileInstance = map->getMapTileInstance(x, y);
            Rectangle tileRect = { (float)(y * Map::side), (float)(x * Map::side), (float)Map::side, (float)Map::side };

            //if (!tileInstance || tileInstance->tileID == 0) continue;

            if (CheckCollisionRecs(bound, tileRect)) {
                if (tile.behavior->isSolid()) {
                    float overlapX = fmin(bound.x + bound.width, tileRect.x + tileRect.width) - fmax(bound.x, tileRect.x);
                    float overlapY = fmin(bound.y + bound.height, tileRect.y + tileRect.height) - fmax(bound.y, tileRect.y);

                    if (overlapX > 0 && overlapY > 0) {
                        if (overlapY < overlapX) { // trên dưới của tile
                            if (velocity.y > 0) { // is falling
                                position.y -= overlapY;
                                velocity.y = 0;
                                onGround = true;
                                isJumpingUp = false;
                                tile.behavior->onFootCollision(this, x, y, map, tileInstance);
                            }
                            else if (velocity.y < 0) { // chạm đầu
                                position.y += overlapY;
                                velocity.y = 0;
                                isJumpingUp = false;
                                tile.behavior->onHeadCollision(this, x, y, map, tileInstance);
                            }

                            
                            //position.y = floor(position.y);
                        }
                        else { // 2 bên của tile 
                            if (velocity.x > 0) { // đang đi sang phải,  đụng bên trái tile
                                position.x -= overlapX;
                            }
                            else if (velocity.x < 0) { // đang đi sang trái, đụng bên phải tile
                                position.x += overlapX;
                            }
                            velocity.x = 0;
                            tile.behavior->onGeneralCollision(this, x, y, map, tileInstance);
                        }
                        bound.x = position.x;
                        bound.y = position.y;
                    }
                }
            }
        }
    }


}