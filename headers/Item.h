#pragma once
#include "raylib.h"
#include "../headers/Character.h"
#include "GameObject.h"

class Item : public GameObject
{
    friend class ItemManager;

public:
    Texture2D texture = Singleton<TextureManager>::getInstance().load(TextureType::ITEM);
    bool collected = false;

    virtual void OnCollected(Character *player) = 0;
    virtual ~Item() = default;

    virtual void update(float deltatime) override = 0;
    virtual void draw() override = 0;
    virtual Rectangle getBound() const override = 0;
    ObjectType getObjectType() const override
    {
        return ObjectType::ITEM;
    }

    // Collide with map
    virtual void onFootCollision(Tile &tile, int row, int col, Map *map, MapTileInstance *tileInstance) override {}
    virtual void onGeneralCollision(Direction collideSide, Tile &tile, int row, int col, Map *map, MapTileInstance *tileInstance) override {}
    virtual void onHeadCollision(Tile &tile, int row, int col, Map *map, MapTileInstance *tileInstance) override {}
    // Collide with other enitities
    virtual void onCollideWith(GameObject *object) override
    {
        if (object->getObjectType() == ObjectType::CHARACTER)
        {
            if (!collected)
                OnCollected(dynamic_cast<Character *>(object));
        }
    }
};
