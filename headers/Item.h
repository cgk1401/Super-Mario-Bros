#pragma once
#include "raylib.h"
#include "../headers/Character.h"

class Item {
public:
    Vector2 position = { 0,0 };
    bool collected = false;

    virtual void Update(float dt) = 0;
    virtual void Draw(const Texture& texure) = 0;
    virtual void OnCollected(Character* player) = 0;
    virtual Rectangle getBound() const = 0;
    virtual ~Item() {}
};
