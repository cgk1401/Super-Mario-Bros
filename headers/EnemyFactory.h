#pragma once
#include "../headers/GoomBa.h"
#include "../headers/PiranhaPlant.h"
#include "../headers/KoopaTroopa.h"
#include  "../headers/Global.h"

class EnemyFactory {
public:
    static Enemy* createEnemy(EnemyType type, Vector2 pos) {
        switch (type) {
            case EnemyType::GOOMBA:
                return new GoomBa(pos);
            case EnemyType::KOOPA:
                return new KoopTroopa(pos);
            case EnemyType::PIRANT_PLANT:
                return new PiranhaPlant(pos);
            default:
                return nullptr;
        }
    }
};
