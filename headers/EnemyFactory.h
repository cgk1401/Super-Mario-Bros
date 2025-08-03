#pragma once
#include "../headers/GoomBa.h"
#include "../headers/PiranhaPlant.h"
#include "../headers/KoopaTroopa.h"
#include "../headers/Global.h"

class EnemyFactory {
public:
    static Enemy* createEnemy(EnemyType type, Vector2 pos, MapTheme theme) {
        switch (type) {
            case EnemyType::GOOMBA:
                return new GoomBa(pos, theme);
            case EnemyType::KOOPA:
            case EnemyType::REDKOOPA:
                return new KoopTroopa(pos, type,theme);
            case EnemyType::PIRANT_PLANT:
                return new PiranhaPlant(pos, theme);
            default:
                return nullptr;
        }
    }
};
