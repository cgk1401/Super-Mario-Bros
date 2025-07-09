#pragma once

class Character;

struct PhysicsConfig {
	float SPEED = 250.0f;
	float MAX_SPEED = 350.0f;
	float ACCELERATION = 500.0f;
	float FRICTION = 700.0f;
	float JUMPFORCE = -400.0f;
	float GRAVITY = 1300.0f;
	float MAXJUMPTIME = 0.32f;
};

class CharacterState {
	friend class Collision;
protected :
	Character* character;

	bool isGround;
	bool isJumpingUp;
	float jumpTimeElapsed;
public :
	CharacterState(Character* character);
	virtual ~CharacterState() = default;

	virtual void SetAnimation(Character* c) = 0;
	virtual void Update(float deltatime) = 0;
	virtual void HandleInput(float deltatime) = 0;
	float approach(float current, float target, float increase);

	Character* getCharacter();
	bool getIsGround();
	void SetBasePosition(float newposition);
};