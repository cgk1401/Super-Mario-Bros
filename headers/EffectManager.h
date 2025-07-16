#pragma once
#include <vector>
#include "raylib.h"
#include "../headers/Animation.h"
#include "../headers/Global.h"
#include "../headers/Timer.h"
#include "../headers/BrickBreakEffect.h"
#include "../headers/BaseEffect.h"
using namespace std;

template <typename T>
class Singleton;

class EffectManager {
    template <typename T>
    friend class Singleton;
private:
    Texture texture;

    //EFFECTs
    vector<BaseEffect*> effects;

    EffectManager();
    ~EffectManager() {};
public:

    //EFFECT METHODs
    void spawnBrickBreak(int row, int col);
    void spawnCoin(int row, int col);
    void explosionEffect(Vector2 pos);

    void update(float dt);
    void draw();
};

