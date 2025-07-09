#pragma once
#include <vector>
#include "raylib.h"
#include "../headers/Animation.h"
#include "../headers/Global.h"
#include "../headers/Timer.h"
#include "../headers/BrickBreakEffect.h"
#include "../headers/BaseEffect.h"
using namespace std;


class EffectManager {
private:
    Texture texture;
    static EffectManager* instance;

    //EFFECTs
    vector<BaseEffect*> effects;
    Animation brickExplosionAnim;
    Animation coinCollectAnim;

    EffectManager();
    ~EffectManager(){delete instance;}
public:

    //EFFECT METHODs
    void spawnBrickBreak(int row, int col);
    void spawnCoin(int row, int col);

    void update(float dt);
    void draw();

    static EffectManager& get(){
        if(!instance)
            instance = new EffectManager;
            return *instance;
    } // singleton
};

