#include "../headers/Item.h"
#include "../headers/TransformState.h"

class Coin : public Item {

public:
    friend class Collision;
    Coin(Vector2 pos, const Animation& ani): animation(ani) { 
        position = pos;
        interactWithMap = false;
       
    }

    void update(float deltatime) override {
        animation.Update(deltatime);
       
    }

    void draw() override {
        Rectangle src = animation.getcurrentframe();
        DrawTexturePro(
            texture,
            src,
            {position.x, position.y, src.width * 4, src.height * 4},
            {0,0}, 0,
            YELLOW
        );
    }

  
    void OnCollected(Character* player) override {
        // Chuyển Mario sang SuperState
        player->collectItem(ItemType::COIN, position);
        Singleton<SoundManager>::getInstance().play(SoundType::COIN);
        collected = true;
    }

    Rectangle getBound() const override {
        Rectangle frame = animation.getcurrentframe();
	
        return {
            position.x,
            position.y,
            frame.width * 4,
            frame.height * 4
        };
    }
private:
    Animation animation;
};
