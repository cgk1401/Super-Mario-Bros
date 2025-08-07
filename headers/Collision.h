#pragma once

class Character;
class Enemy;
class Map;
class Mushroom;
class Star;
#include "FireBall.h"
#include "BowserFireBall.h"]

class Collision{
public:
    static void handlePlayerCollision(Character* mario, Map* map, bool hasNotified = false);
    static void handleEnemyCollision(Enemy* enemies, Map* map);
    static void handleMushroomCollisionMap(Mushroom* mushroom, Map* map);
    static void handleStarCollision(Star* star, Map* map);
    static void handleFireBallCollisionMap(FireBall* fire, Map* map);
    
    static void handleEnemy_EnemyCollison(vector<Enemy*>& enemies);
    static void handlePlayer_EnemyCollision(Character* player, vector<Enemy*>& enemies);
    static void handleFireball_EnemyCollision(FireBall* fireball, vector<Enemy*> enemies);
    //static void handleBowserball_CharacterCollision(BowserFireBall* bowserfireball, Character* character);
};