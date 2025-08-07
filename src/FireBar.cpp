#include "FireBar.h"
#include "TextureManager.h"
#include "Character.h"
#define pi 3.14f

FireBar::FireBar(Vector2 _position, const Animation& ani){
    texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIO);

    fireAnimation.durationtime = 0.1f;
    fireAnimation.frame.push_back({ 172, 185, 8, 8 });
	fireAnimation.frame.push_back({ 182, 185, 8, 8 });
	fireAnimation.frame.push_back({ 192, 185, 8, 8 });
	fireAnimation.frame.push_back({ 202, 185, 8, 8 });

    position = _position;
    this->bar.resize(6);
    const float fire_width = 3.5 * 8;
    for(int i = 0 ; i < bar.size(); i++){
        bar[i].x = fire_width * i + position.x;
        bar[i].y = position.y;
        bar[i].width = bar[i].height = fire_width;
    }
    angle = 0;
}
void FireBar::update(float deltatime) {
    angle += 2;
    fireAnimation.Update(deltatime);
    const float fire_width = 3.5 * 8;

    for (int i = 0; i < bar.size(); i++) {
        float distanceFromCenter = i * fire_width;
        
        float localX = 0;
        float localY = -distanceFromCenter;

        float rad = angle * DEG2RAD;
        float rotatedX = localX * cos(rad) - localY * sin(rad);
        float rotatedY = localX * sin(rad) + localY * cos(rad);

        bar[i].x = position.x + rotatedX;
        bar[i].y = position.y + rotatedY;
    }
}
void FireBar::draw() {
    for(auto& fire: bar){
        DrawTexturePro(texture,
                        fireAnimation.getcurrentframe(),
                        fire, 
                        {0,0},
                        0,
                        WHITE
                        );
    }

}

Rectangle FireBar::getBound() const{
    return {0,0,0,0};
}

void FireBar::OnCollected(Character* player){
    
}
void FireBar::checkCollision(Character* player){
    for(auto& rect: bar){
        if(CheckCollisionRecs(player->getBound(), rect)){
            player->onDead();
        }
    }
}

