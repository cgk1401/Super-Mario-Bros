#pragma once
#include <string>
#include <map>
using namespace std;

enum class EventType {
    COIN_COLLECT,
    BRICK_BREAK,
    BRICK_COIN_REVEAL,
    BRICK_POWERUP_REVEAL,

    ENEMY_KILL_GOOMBA,
    ENEMY_KILL_KOOPA,
    ENEMY_KILL_BY_SHELL,
    ENEMY_KILL_BY_FIREBALL,
    ENEMY_MULTI_KILL,

    FLAG_REACH,
    TIME_BONUS,

    POWERUP_COLLECT_MUSHROOM,
    POWERUP_COLLECT_FLOWER,
    POWERUP_COLLECT_STAR,
    ITEM_COLLECT_1UP,

    ON_DEATH,
    FLAG_POLE,
};

struct EventInfo {
    int score = 0;
    string label = "";
    bool showEffect = false;
};

class EventDataBase {
    template <typename T>
    friend class Singleton;
private:
    map<EventType, EventInfo> eventMap;

    EventDataBase();
   
public:
    ~EventDataBase();   
    map<EventType, EventInfo> getMap() const{
        return eventMap;
    }

};