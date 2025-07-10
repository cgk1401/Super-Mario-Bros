#include "../headers/Item.h"
#include "../headers/TransformState.h"
#include "../headers/Map.h"

#define GRAVITY 1000


class Star : public Item {
    private:
    Animation animation;
    float bounce = 80.0f;
    bool startRunning;
    float height;
    float startPos;
    Vector2 velocity = {0,0};
    Direction direction;
    bool onGround = false;

    const float BOUNCE_FORCE = -sqrt(2 * GRAVITY * (Map::TILE_SIZE * 2));
public:
    friend class Collision;
    Star(Vector2 pos, const Animation& ani): animation(ani) { 
        position = pos; 
         startPos = pos.y;
        startRunning = false;
        height = animation.getcurrentframe().height * 4;
        direction = Direction::Right;
    }

    void Update(float dt) override {
        animation.Update(dt);
    
        if(!startRunning){
            velocity.x = 0;
            velocity.y = -100;

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
            velocity.y += GRAVITY * dt;
        }
        

        position.x += velocity.x * dt;
        position.y += ((startRunning ? sin(GetTime() * (-5.0f)) * bounce : 0) + velocity.y) * dt ;
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
        // become invincible
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

    bool isRunning() const {return startRunning;}
};
