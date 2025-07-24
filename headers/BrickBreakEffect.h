#pragma once
#include <vector>
#include "raylib.h"
#include "../headers/Animation.h"
#include "../headers/Global.h"
#include "../headers/Timer.h"
#include "../headers/BaseEffect.h"
using namespace std;

class BrickBreakEffect : public BaseEffect {
private:
    Vector2 pos;
    vector<Vector2> particle;
    vector<Vector2> velocity;
    Animation anim;
    Timer time;
public:
    BrickBreakEffect() {}
    BrickBreakEffect(Vector2 position);
    ~BrickBreakEffect();
    
    void update(float dt) override;
    void draw(const Texture2D& texture) override;
    bool isFinished() const override;
   
};

