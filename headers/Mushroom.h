#include "../headers/Item.h"
#include "../headers/TransformState.h"

class Mushroom : public Item {
private:
    Direction direction;
    Animation animation;
    bool startRunning;
    float height;
    float startPos;
    bool onGround;
    Vector2 velocity = {0,0};
public:
    friend class Collision;
    Mushroom(Vector2 pos, const Animation& ani): animation(ani) { 
        position = pos;
        startPos = pos.y;
        direction = Direction::Right;
        startRunning = false;
        onGround = false;
        height = animation.getcurrentframe().height * 4;
    }

    void Update(float dt) override {
        animation.Update(dt);
        const float gravity = 1000;
        
        if(!startRunning){
            velocity.x = 0;
            velocity.y =  -100;

            if(position.y + height < startPos){
                startRunning = true;
            }
        }
        else{
            
            if(direction == Direction::Right){
                velocity.x = 100;
            }
            else if (direction == Direction::Left){
                velocity.x = -100;
            }
            velocity.y += gravity * dt;
        }
        
        position.x += velocity.x * dt;
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

    void changeDirection(Direction newDirection){
        if(direction != newDirection)
            direction = newDirection;
    }
    void OnCollected(Character* player) override {
        // Chuyển Mario sang SuperState
        if(player->getCharacterStateType() == CharacterStateType::NormalState)
            player->ChangeMiddleState(CharacterStateType::SuperState);
        player->collectItem(ItemType::MUSHROOM, position);
        collected = true;
    }

    bool isRunning() const{
        return startRunning;
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
