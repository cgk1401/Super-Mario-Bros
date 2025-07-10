#pragma once

class Character;
class Enemy;
class Map;
class Mushroom;
class Star;

class Collision{
public:
    static void handlePlayerCollision(Character* mario, Map* map);
    static void handleEnemyCollision(Enemy* enemies, Map* map);
    static void handleMushroomCollisionMap(Mushroom* mushroom, Map* map);
    static void handleStarCollision(Star* star, Map* map);
};