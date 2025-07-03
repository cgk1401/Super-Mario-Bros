#pragma once

#include "CharacterState.h"

class NormalState : public CharacterState {
private :
	const float SPEED = 250.0f;
	const float MAX_SPEED = 350.0f;
	const float ACCELERATION = 500.0f;
	const float FICTION = 700.0f;
	const float JUMPFORCE = -400.0f;
	const float GRAVITY = 1300.0f;
	const float MAXJUMPTIME = 0.32f; // thời gian tối đa giữ phím đã tăng bước nhảy
	float BasePosition;
	bool isGround;
	bool isJumpingUp;
	float jumpTimeElapsed;
public :
	NormalState(Character* character);
	~NormalState() override = default;

	void SetAnimation(Character* c) override;
	void Update(float deltatime) override;
	void HandleInput(float deltatime) override;
};