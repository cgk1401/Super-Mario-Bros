#pragma once
#include "Animation.h"
#include "../headers/Map.h"
#include "../headers/Global.h"

class Character;

class Enemy {
protected:
	Vector2 position;
	Rectangle bound;
	Texture texture;

	Direction direction;
	bool onGround;
	Vector2 velocity;
public:
	Enemy() : 
		position({ 0,0 }), 
		bound({ 0,0,0,0 }), 
		texture({ 0 }), 
		onGround(true), 
		velocity({0,0}),
		direction(Direction::Left) {}

	friend class Collision;
	virtual ~Enemy() = default;
	virtual void Update(float deltatime, Map* map) = 0;
	virtual void Draw() = 0;
	virtual void LoadSource() = 0;
	virtual void onDeath(DeathType type, Character* player = nullptr) = 0;
	virtual bool isDead() = 0; 
	virtual void changeDirection(Direction newDirection) {
		if (direction != newDirection) 
			direction = newDirection;
	}
	

	virtual bool isActive() const {
		Vector2 screenPos = GetWorldToScreen2D(this->position, Global::camera);
		float tolerance = Map::TILE_SIZE;
		return (
			screenPos.x >= -tolerance &&
			screenPos.x <= screenWidth + tolerance &&
			screenPos.y >= -tolerance &&
			screenPos.y <= screenHeight + tolerance
			);
	}
};