#include "../headers/BrickBreakEffect.h"

BrickBreakEffect::BrickBreakEffect(Vector2 position)
        : pos(position){
    
    vector<Rectangle> brickFrames;
    for(int i = 0; i < 2; i++){
        brickFrames.push_back(Rectangle{(float)(180 + i * 10), 26, 8, 8});
    }

    anim.frame = brickFrames;
    anim.durationtime = 0.08f;

    anim.reset();
    time.start(0.2f);

    particle.resize(4);
    velocity.resize(4);

    for (int i = 0; i < 4; i++) {
        particle[i] = position;
    }

    
    for (int i = 0; i < 4; ++i) {
        particle[i] = position;

        float vx = (i < 2) ? -70.0f : 70.0f;
        float vy = (i % 2 == 0) ? -350.0f : -250.0f; // cao/thấp

        velocity[i] = { vx, vy };
    }
}

BrickBreakEffect::~BrickBreakEffect(){
    particle.clear();
    velocity.clear();
}

void BrickBreakEffect::update(float dt) {
    anim.Update(dt);
    time.update(dt);

    for (int i = 0; i < 4; i++) {
        particle[i].x += velocity[i].x * dt;
        particle[i].y += velocity[i].y * dt;

        velocity[i].y += 1000 * dt;
    }
}


void BrickBreakEffect::draw(const Texture2D& texture) {
    for (auto& p : particle) {
        DrawTexturePro(texture, anim.getcurrentframe(),
            { p.x, p.y, anim.getcurrentframe().width * 3, anim.getcurrentframe().height * 3 },
            { 0,0 }, 0, WHITE);
    }
}

bool BrickBreakEffect::isFinished() const {

    for (const auto& p : particle) {
        if (p.y < screenHeight + 50) return false;
    }
    return true;
}
   