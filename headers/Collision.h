#pragma once
#include <vector>
using namespace std;

class Character;
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
    void handleEnemyCollision(vector<Character*> enemies, Map* map);
};