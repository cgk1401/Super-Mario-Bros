#pragma once
#include <vector>
#include "raylib.h"
#include "../headers/Animation.h"
#include "../headers/Global.h"
#include "../headers/Timer.h"
#include "../headers/BaseEffect.h"
using namespace std;

class KoopaDeathEffect : public BaseEffect {
private:
    Texture2D texture;
    Vector2 pos;
    Animation anim;
    float speed = -300;
public:
    KoopaDeathEffect() {}
    KoopaDeathEffect(Vector2 position, const Texture2D& texture, Rectangle frame);
    
    void update(float dt) override;
    void draw(const Texture2D& texture) override;
    bool isFinished() const override;
};


