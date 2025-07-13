#include "../headers/FireBallExplosionEffect.h"

FireBallExplosionEffect::FireBallExplosionEffect(Vector2 pos): pos(pos){
    vector<Rectangle> frames;
    for(int i = 0; i < 4; i++){
        frames.push_back({(float)(180 + 18 * i), 64, 16, 16});
    }

    anim.frame = frames;
    anim.durationtime = 0.1;
    anim.reset();
}
void FireBallExplosionEffect::update(float dt) {
    anim.Update(dt);

}
void FireBallExplosionEffect::draw(const Texture2D& texture) {
    Rectangle src = anim.getcurrentframe();
    const float scale = 4;
    DrawTexturePro(texture,
                    src,
                    {pos.x, pos.y, src.width * scale, src.height * scale},
                    {0,0}, 0, WHITE        
                    );

}
bool FireBallExplosionEffect::isFinished() const {
    //cout << anim.currentframe << endl;
    if(anim.currentframe + 1 == anim.frame.size()){
        return true;
    }
    return false;
}