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
    }

    void Update(float dt) override {
        // Không di chuyển
        animation.Update(dt);
        const float gravity = 1000;
           if(!fullyAppear){
            velocity.y = -100 ;

            if(position.y + height < startPos){
                fullyAppear = true;
            }
        }
        else velocity.y = 0;

        position.y += velocity.y * dt;
    }

    void Draw(const Texture& texture) override {
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
            return;
        }
        player->ChangeMiddleState(CharacterStateType::FireState);
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
