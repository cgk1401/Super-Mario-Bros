#pragma once

class Character;
#include "Global.h"
#include "AnimationManager.h"

struct PhysicsConfig {
	float SPEED = 350.0f;
	float MAX_SPEED = 450.0f;
	float ACCELERATION = 500.0f;
	float FRICTION = 700.0f;
	float JUMPFORCE = -450.0f;
	float GRAVITY = 2000.0f;
	float MAXJUMPTIME = 0.7f;
};

class CharacterState {
	friend class Collision;
protected :
	Character* character;

public :
	CharacterState(Character* character);
	virtual ~CharacterState() = default;

	virtual void SetAnimation(Character* c) = 0;
	virtual void Update(float deltatime) = 0;
	virtual void HandleInput(float deltatime) = 0;
	float approach(float current, float target, float increase);
	virtual CharacterStateType getStateType() = 0;

	Character* getCharacter();
	bool getonGround();
	void SetBasePosition(float newposition);
};