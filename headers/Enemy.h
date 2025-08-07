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
	Enemy();

	friend class Collision;
	virtual ~Enemy() = default;
	virtual void LoadSource() = 0;
	virtual void onDeath(DeathType type, Character* player = nullptr) = 0;
	virtual bool isDead() = 0; 

	virtual EnemyType getType() const = 0;
	virtual void changeDirection(Direction newDirection);
	

	virtual bool isActive() const;

	//_______Inherit GameObject_________
	virtual void draw() override = 0;
	virtual void update(float deltatime) override = 0;
	virtual Rectangle getBound() const override = 0;
	ObjectType getObjectType() const;

	//Collide with map
	virtual void onFootCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override;
	virtual void onGeneralCollision(Direction collideSide, Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance);
	virtual void onHeadCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override;
	
	//Collide with entities
    virtual void onCollideWith(GameObject* object) override = 0;
};