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

    void update(float deltatime) override {
        animation.Update(deltatime);
        const float gravity = 1000;
        
        if(!startRunning){
            interactWithMap = false;
            velocity.x = 0;
            velocity.y =  -100;

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
            velocity.y += gravity * deltatime;
        }
        
        position.x += velocity.x * deltatime;
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

    void onFootCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override {
          Rectangle tileRect = { (float)(col * Map::TILE_SIZE), (float)(row * Map::TILE_SIZE), (float)Map::TILE_SIZE, (float)Map::TILE_SIZE };
          Rectangle bound = getBound();
         if (tileInstance->offsetPos.y < 0) {
            position.y = tileRect.y - bound.height - 3;
            velocity.y = -300;
            onGround = false;
            if (velocity.x > 0) { 
                changeDirection(Direction::Left);
            }
            else if (velocity.x < 0) { 
                changeDirection(Direction::Right);
            }
        }
        else if (tileInstance->offsetPos.y == 0){
            position.y = tileRect.y - bound.height - 0.3f;
            velocity.y = 0;
            onGround = true;
        }
    }
    void onGeneralCollision(Direction collideSide, Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override {
        if(collideSide == Direction::Left){
			direction = Direction::Right;
		}
		else direction = Direction::Left;
    }
    void onHeadCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override {}
};
