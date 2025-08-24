#pragma once
#include "../headers/GoomBa.h"
#include "../headers/PiranhaPlant.h"
#include "../headers/KoopaTroopa.h"
#include "../headers/KoopaParatroopa.h"
#include "../headers/Global.h"
#include "Bowser.h"
// Creator (Abstract Factory)
class EnemyFactory
{
public:
    virtual ~EnemyFactory() = default;
    virtual Enemy *createEnemy(Vector2 pos, MapTheme theme) = 0; // Factory Method
};

// Concrete Factories
class GoomBaFactory : public EnemyFactory
{
public:
    Enemy *createEnemy(Vector2 pos, MapTheme theme) override
    {
        return new GoomBa(pos, theme);
    }
};

class KoopaTroopaFactory : public EnemyFactory
{
private:
    EnemyType type;

public:
    KoopaTroopaFactory(EnemyType t) : type(t) {}
    Enemy *createEnemy(Vector2 pos, MapTheme theme) override
    {
        return new KoopTroopa(pos, type, theme);
    }
};

class PiranhaPlantFactory : public EnemyFactory
{
public:
    Enemy *createEnemy(Vector2 pos, MapTheme theme) override
    {
        return new PiranhaPlant(pos, theme);
    }
};

class BowserFactory : public EnemyFactory
{
public:
    Enemy *createEnemy(Vector2 pos, MapTheme theme) override
    {
        return new Bowser(pos, theme);
    }
};

class KoopaParatroopaFactory : public EnemyFactory
{
public:
    Enemy *createEnemy(Vector2 pos, MapTheme theme) override
    {
        return new KoopaParatroop(pos, theme);
    }
};
