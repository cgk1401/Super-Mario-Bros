#pragma once

class Character;
class Enemy;
class Map;

class Collision{
public:
    static void handlePlayerCollision(Character* mario, Map* map);
    static void handleEnemyCollision(Enemy* enemies, Map* map);
};