#pragma once

#include "CharacterState.h"
#include <vector>
#include "FireBall.h"
#include "../headers/Character.h"
#include "../headers/TextureManager.h"

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
	CharacterStateType getStateType() override;

	std::vector <FireBall*> getFireBall();
};
