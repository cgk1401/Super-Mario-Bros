#pragma once
#include <raylib.h>

class Character {
protected:
    Vector2 pos;
public:
    void updatePos(Vector2 newPos);
};