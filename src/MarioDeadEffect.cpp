#include "../headers/MarioDeadEffect.h"
#include "../headers/TextureManager.h"

MarioDeadEffect::MarioDeadEffect(Vector2 position, const Texture2D& texture, Rectangle frame) : pos(position), texture(texture) {

    vector<Rectangle> frames;
    frames.push_back(frame);


    anim.frame = frames;
    anim.durationtime = 0.1;
    anim.reset();
}
void MarioDeadEffect::update(float dt) {
    anim.Update(dt);
    
    const float gravity = 1000;
    speed += gravity * dt;
    pos.y += speed * dt;

}
void MarioDeadEffect::draw(const Texture2D& texture) {
   
    Rectangle src = anim.getcurrentframe();
    const float scale = 4;
    DrawTexturePro(this->texture,
        src,
        { pos.x, pos.y, src.width * scale, src.height * scale },
        { 0,0 }, 0, WHITE
    );

}
bool MarioDeadEffect::isFinished() const {
    return pos.y > screenHeight + 50;
}