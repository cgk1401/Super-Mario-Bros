#pragma once

class Character;
class Enemy;
class Map;

class Collision{
private:
    static Collision* instance;

    ~Collision();
public:

    static Collision* getInstance() {
        if (!instance)
            instance = new Collision;
        return instance;
    }
    void handlePlayerCollision(Character* mario, Map* map);
    void handleEnemyCollision(Enemy* enemies, Map* map);
};