#include "../headers/Item.h"
#include "../headers/FireState.h"

class Flower : public Item {
private:
    Animation animation;
      bool fullyAppear;
        float height;
        float startPos;
        Vector2 velocity = {0,0};
public:
    Flower(Vector2 pos, const Animation& ani): animation(ani) { 
        position = pos;
        startPos = pos.y;
        fullyAppear = false;
        height = animation.getcurrentframe().height * 4;
        this->interactWithMap = false;
    }

    void update(float deltatime) override {
        // Không di chuyển
        animation.Update(deltatime);
        const float gravity = 1000;
           if(!fullyAppear){
            velocity.y = -100 ;

            if(position.y + height < startPos){
                fullyAppear = true;
            }
        }
        else velocity.y = 0;

        position.y += velocity.y * deltatime;
    }

    void draw() override {
        Rectangle src = animation.getcurrentframe();
        DrawTexturePro(
            texture,
            src,
            {position.x, position.y, src.width * 4, src.height * 4},
            {0,0}, 0, WHITE
        );
    }

    void OnCollected(Character* player) override {
        CharacterState* currentState = player->GetCurrentState();
        if(currentState == dynamic_cast<FireState*>(currentState)){
            //get more coin scores
            player->collectItem(ItemType::FLOWER, position);
            collected = true;
            return;
        }
        player->ChangeMiddleState(CharacterStateType::FireState);
        player->collectItem(ItemType::FLOWER, position);
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
};
