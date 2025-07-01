#pragma once
#include <vector>
#include "raylib.h"
#include "../headers/Animation.h"
#include "../headers/Global.h"
#include "../headers/Timer.h"
#include "../headers/BaseEffect.h"
using namespace std;



class CoinCollectEffect : public BaseEffect {
private:
    Vector2 pos;
    float height;
    Vector2 coinPos;
    float coinHeight;
    Animation anim;
    Timer time;

public:
    CoinCollectEffect() {}
    CoinCollectEffect(Vector2 position, const Animation& templateAnim);
    
    void update(float dt) override;
    void draw(const Texture2D& texture) override;
    bool isFinished() const override;
   
};

