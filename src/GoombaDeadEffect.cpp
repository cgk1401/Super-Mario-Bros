#include "../headers/GoombaDeadEffect.h"
#include "../headers/TextureManager.h"

GoombaDeadEffect::GoombaDeadEffect(Vector2 pos) : pos(pos) {
    texture = TextureManager::get().load(TextureType::ENEMY);

    vector<Rectangle> frames;
    frames.push_back({ 0, 16, 16, -16 });


    anim.frame = frames;
    anim.durationtime = 0.1;
    anim.reset();
}
void GoombaDeadEffect::update(float dt) {
    anim.Update(dt);
    
    const float gravity = 1000;
    speed += gravity * dt;
    pos.y += speed * dt;
}
void GoombaDeadEffect::draw(const Texture2D& texture) {
    Rectangle src = anim.getcurrentframe();
    const float scale = 3;
    DrawTexturePro(this->texture,
        src,
        { pos.x, pos.y, src.width * scale,  src.height * scale },
        { 0,0 }, 0, WHITE
    );

}
bool GoombaDeadEffect::isFinished() const {
    return pos.y > screenHeight + 50;
}