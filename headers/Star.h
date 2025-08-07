#include "../headers/Item.h"
#include "../headers/TransformState.h"
#include "../headers/Map.h"


class Star : public Item {
    private:
    Animation animation;
    float bounce = 800.0f;
    bool startRunning;
    float height;
    float startPos;
    Vector2 velocity = {0,0};
    Direction direction;
    bool onGround = false;

    const float BOUNCE_FORCE = -sqrt(2 * 1000 * (Map::TILE_SIZE * 2));
public:
    friend class Collision;
    Star(Vector2 pos, const Animation& ani): animation(ani) { 
        position = pos; 
         startPos = pos.y;
        startRunning = false;
        height = animation.getcurrentframe().height * 4;
        direction = Direction::Right;
    }

    void update(float deltatime) override {
        animation.Update(deltatime);
        if(!startRunning){
            velocity.x = 0;
            velocity.y = -100;
            interactWithMap = false;

            if(position.y + height < startPos){
                startRunning = true;
            }
        }
        else{
            interactWithMap = true;
            
            if(direction == Direction::Right){
                velocity.x = 100;
            }
            else if (direction == Direction::Left){
                velocity.x = -100;
            }
            velocity.y += 1000 * deltatime;
        }
        

        position.x += velocity.x * deltatime;
        position.y +=  velocity.y * deltatime ;
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
        // become invincible
        player->ChangeMiddleState(CharacterStateType::StarmanState);
        player->collectItem(ItemType::STAR, position);
        collected = true;
    }

    Rectangle getBound() const override {
        Rectangle frame = animation.getcurrentframe();
        float delta = 0.5f;
        return {
            position.x + delta,
            position.y,
            frame.width * 4 - delta * 2,
            frame.height * 4
        };
    }

    bool isRunning() const {return startRunning;}

    void onFootCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override {
        velocity.y = BOUNCE_FORCE;
    }
    void onGeneralCollision(Direction collideSide, Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override {
        if(collideSide == Direction::Left){
			direction = Direction::Right;
		}
		else direction = Direction::Left;
    }
    void onHeadCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override {}
};
