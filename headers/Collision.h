#pragma once

class Character;
class Enemy;
class Map;
class Mushroom;
class Star;
class BowserFireBall;
class Lift;
class FireBall;
#include "GameObject.h"
#include <vector>

using namespace std;

class Collision
{
public:
    static void handleMapCollision(GameObject *object, Map *map);
    static void handleObjectsCollision(GameObject *a, GameObject *b);
    static void handleMultipleObjectCollisions(vector<GameObject *> &objects);
};