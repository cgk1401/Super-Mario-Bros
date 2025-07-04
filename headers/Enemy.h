#pragma once
#include "Animation.h"
#include "../headers/Map.h"
class Enemy {
protected:
	Vector2 position;
	Rectangle bound;
	Texture texture;

	bool onGround;
	Vector2 velocity;
public:
	Enemy() : 
		position({ 0,0 }), 
		bound({ 0,0,0,0 }), 
		texture({ 0 }), 
		onGround(true), 
		velocity({0,0}) {}

	friend class Collision;
	virtual ~Enemy() = default;
	virtual void Update(float deltatime, Map* map) = 0;
	virtual void Draw() = 0;
	virtual void LoadSource() = 0;
	virtual bool isDead() = 0; 
};