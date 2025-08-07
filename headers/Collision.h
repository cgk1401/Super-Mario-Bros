#pragma once

class Character;
class Enemy;
class Map;
class Mushroom;
class Star;
#include "FireBall.h"
#include "GameObject.h"
class Collision{
public:
    static void handleMapCollision(GameObject* object, Map* map);
    static void handleObjectsCollision(GameObject* a, GameObject* b);
    static void handleMultipleObjectCollisions(vector<GameObject*>& objects);
};