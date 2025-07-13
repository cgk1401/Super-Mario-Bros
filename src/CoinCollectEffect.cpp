#include "../headers/CoinCollectEffect.h"
#include "../headers/Map.h"

CoinCollectEffect::CoinCollectEffect(Vector2 position): pos(position){
    //COIN COLLECT
    vector<Rectangle> coinFrames;
    for(int i = 0; i < 4; i++){
        coinFrames.push_back(Rectangle{(float)(180 + i * 10), 36, 8, 16});
    }

    anim.frame = coinFrames;
    anim.durationtime = 0.07;

    anim.reset();
    coinPos = position; //spawn position
    height = 15;
    time.start(1);
}

void CoinCollectEffect::update(float dt) {
    anim.Update(dt);
    time.update(dt);

    if(time.isRunning()){
        if(time.getProgress() > 0.5f){
            coinPos.y += +height * time.getProgress();   
        }
        else{
            coinPos.y += -height * time.getProgress(); 
        }
    }
    
    
}
void CoinCollectEffect::draw(const Texture2D& texture) {
    Rectangle src = anim.getcurrentframe();
    const float scale = 3;
    coinHeight = src.height * scale;
    DrawTexturePro(texture,
                    src,
                    {coinPos.x, coinPos.y, src.width * scale, src.height * scale},
                    {0,0}, 0, WHITE        
                    );

}
bool CoinCollectEffect::isFinished() const {
    return coinPos.y > pos.y ;
}