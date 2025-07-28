#pragma once
#include <vector>
#include "raylib.h"
#include "../headers/Animation.h"
#include "../headers/Global.h"
#include "../headers/Timer.h"
#include "../headers/BrickBreakEffect.h"
#include "../headers/BaseEffect.h"
#include "PointEffect.h"
#include "OBSERVER/Observer.h"
using namespace std;

template <typename T>
class Singleton;

class EffectManager : public Observer{
    template <typename T>
    friend class Singleton;
private:
    Texture texture;
    //EFFECTs
    vector<BaseEffect*> effects;
    vector<BaseEffect*> hidden_effects;
    EffectManager();
    ~EffectManager() {};
public:

    //EFFECT METHODs
    void spawnBrickBreak(int row, int col, MapTheme theme);
    void spawnCoin(int row, int col);
    void explosionEffect(Vector2 pos);
    void goombaDead(Vector2 pos);
    void marioDead(Vector2 position, const Texture2D& texture, Rectangle frame);
    void koopaDeath(Vector2 position, const Texture2D& texture, Rectangle frame);

    void update(float dt);
    void draw();
    void drawHiddenEffects();

    void onNotify(const EventType& event, void* data = nullptr);
};

