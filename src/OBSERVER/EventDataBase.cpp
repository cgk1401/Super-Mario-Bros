#include "OBSERVER/EventDataBase.h"

EventDataBase::EventDataBase(){
    eventMap[EventType::COIN_COLLECT]             = {100, "100", true};
    eventMap[EventType::BRICK_BREAK]              = {50,  "50",  true};
    eventMap[EventType::BRICK_COIN_REVEAL]        = {0,   "",     false};
    eventMap[EventType::BRICK_POWERUP_REVEAL]     = {0,   "",     false};

    eventMap[EventType::ENEMY_KILL_GOOMBA]        = {100, "100", true};
    eventMap[EventType::ENEMY_KILL_KOOPA]         = {200, "200", true};
    eventMap[EventType::ENEMY_KILL_BY_SHELL]      = {300, "300", true};
    eventMap[EventType::ENEMY_KILL_BY_FIREBALL]   = {200, "200", true};
    eventMap[EventType::ENEMY_MULTI_KILL]         = {500, "500", true};

    eventMap[EventType::FLAG_REACH]               = {400, "400", true};
    eventMap[EventType::TIME_BONUS]               = {0,   "",     false}; // handled separately

    eventMap[EventType::POWERUP_COLLECT_MUSHROOM] = {1000,   "1000",     true};
    eventMap[EventType::POWERUP_COLLECT_FLOWER]     = {1000,   "1000",     false};
    eventMap[EventType::POWERUP_COLLECT_STAR]     = {1000,   "1000",     false};
    eventMap[EventType::ITEM_COLLECT_1UP]         = {0,   "1UP",  true};
}

EventDataBase::~EventDataBase(){
    eventMap.clear();
}
