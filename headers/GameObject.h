#pragma once
#include <raylib.h>
#include "Map.h"
enum class ObjectType
{
    CHARACTER,
    ITEM,
    ENEMY
};

class GameObject
{
    friend class Collision;

public:
    GameObject()
    {
        velocity = {0, 0};
        position = {0, 0};
        onGround = false;
        interactWithMap = true;
    }
    virtual ~GameObject() = default;
    virtual void update(float deltatime) = 0;
    virtual void draw() = 0;
    virtual Rectangle getBound() const = 0;
    virtual ObjectType getObjectType() const = 0;

    // Collide with map
    virtual void onFootCollision(Tile &tile, int row, int col, Map *map, MapTileInstance *tileInstance) = 0;
    virtual void onGeneralCollision(Direction collideSide, Tile &tile, int row, int col, Map *map, MapTileInstance *tileInstance) = 0;
    virtual void onHeadCollision(Tile &tile, int row, int col, Map *map, MapTileInstance *tileInstance) = 0;
    // Collide with other enitities
    virtual void onCollideWith(GameObject *object) = 0;

public:
    bool interactWithMap;
    Vector2 velocity;
    Vector2 position;
    bool onGround;
};