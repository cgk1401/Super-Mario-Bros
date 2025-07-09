#pragma once

#include <raylib.h>
#include "Animation.h"
#include "CharacterState.h"
#include "Character.h"

class FireState;

class FireBall {
	friend class FireState;
private:
	Vector2 position;
	Vector2 velocity;

	Animation* animation;
	float scale;

	const float FIREBALL_SPEEDX = 350.0f;
	const float FIREBALL_SPEEDY = 800.0f;
	const float FIREBALL_LIFETIME = 2.0f;
	const float BOUNCE_VELOCITY = -200.f;

	//bool isActive;
	float positionGround;
	float currentLifeTime;
public:
	FireBall(Character* character, float positionGround);
	FireBall(Vector2 position, Character* character, float positionGround);
	~FireBall();

	bool isActive;
	void SetAnimation(Character* character);
	void SetVelocity(Vector2 velocity);
	void Update(float deltatime);
	void Draw(Character* character);
	void Deactivate();

	void ActiveStatus(float deltatime);
};