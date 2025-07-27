#pragma once
#include <vector>
#include "raylib.h"
#include "../headers/Animation.h"
#include "../headers/Global.h"
#include "../headers/Timer.h"
#include "../headers/BaseEffect.h"
#include "OBSERVER/EventDataBase.h"
using namespace std;

class PointEffect : public BaseEffect {
private:
    Vector2 pos;
    float speed = 60.0f;
    Timer time;
    EventType event;
public:
    PointEffect(Vector2 position, EventType event);
    ~PointEffect();
    
    void update(float dt) override;
    void draw(const Texture2D& texture) override;
    bool isFinished() const override;
   
};

