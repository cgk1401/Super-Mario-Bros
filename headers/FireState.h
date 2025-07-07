#pragma once

#include "CharacterState.h"
#include <vector>
#include "FireBall.h"

class FireBall;

class FireState : public CharacterState {
	friend class FireBall;

private:
	PhysicsConfig config;
	std::vector <FireBall*> fireballs;

	const int maxFireBalls = 10;
public:
	FireState(Character* character);
	~FireState() override;

	void SetAnimation(Character* c) override;
	void Update(float deltatime) override;
	void HandleInput(float deltatime) override;

	std::vector <FireBall*> getFireBall();
};
