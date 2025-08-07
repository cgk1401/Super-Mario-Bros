#pragma once
#include "Animation.h"
#include "ConcreteTileBehavior.h"
#include "GameObject.h"
class Character;

class Enemy : public GameObject{
protected:
	Texture texture;
	Direction direction;
	MapTheme theme;
public:
	Enemy() :
		texture({ 0 }), 
		direction(Direction::Left),
		theme(MapTheme::OVERWORLD) {}

	friend class Collision;
	virtual ~Enemy() = default;
	virtual void LoadSource() = 0;
	virtual void onDeath(DeathType type, Character* player = nullptr) = 0;
	virtual bool isDead() = 0; 

	virtual EnemyType getType() const = 0;
	virtual void changeDirection(Direction newDirection) {
		if (direction != newDirection) 
			direction = newDirection;
	}
	

	virtual bool isActive() const {
		Vector2 screenPos = GetWorldToScreen2D(this->position, Global::camera);
		float tolerance = Map::TILE_SIZE;
		return (
			screenPos.x <= screenWidth + tolerance &&
			screenPos.y >= -tolerance &&
			screenPos.y <= screenHeight + tolerance
			);
	}


	virtual void draw() override = 0;
	virtual void update(float deltatime) override = 0;
	virtual Rectangle getBound() const override = 0;
	ObjectType getObjectType() const {
		return ObjectType::ENEMY;
	} 

	void onFootCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override {
		if(tileInstance->offsetPos.y != 0 ){
			onDeath(DeathType::FALLING);
		}
		else if (auto brickstate = dynamic_cast<BrickTileState*>(tileInstance->state)){
				if(brickstate->hasBroken == true)
					onDeath(DeathType::FALLING);
		}
	}
	void onGeneralCollision(Direction collideSide, Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override{
		if(collideSide == Direction::Left){
			direction = Direction::Right;
		}
		else direction = Direction::Left;
	}
    void onHeadCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override{}
	
    virtual void onCollideWith(GameObject* object) override = 0;
};