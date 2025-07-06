#pragma once

#include "CharacterState.h"

class FireState : public CharacterState {
private:
	PhysicsConfig config;

public:
	FireState(Character* character);
	~FireState() override = default;

	void SetAnimation(Character* c) override;
	void Update(float deltatime) override;
	void HandleInput(float deltatime) override;
};
