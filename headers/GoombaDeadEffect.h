#pragma once
#include <vector>
#include "raylib.h"
#include "../headers/Animation.h"
#include "../headers/Global.h"
#include "../headers/Timer.h"
#include "../headers/BaseEffect.h"
using namespace std;

class GoombaDeadEffect : public BaseEffect {
private:
    Texture2D texture;
    Vector2 pos;
    Animation anim;
    float speed = -100;
public:
    GoombaDeadEffect() {}
    GoombaDeadEffect(Vector2 position);
    
    void update(float dt) override;
    void draw(const Texture2D& texture) override;
    bool isFinished() const override;
};


