#pragma once

#include "CharacterState.h"

class SuperState : public CharacterState {
private:
	PhysicsConfig config;
public:
	SuperState(Character* character);
	~SuperState() override = default;

	void SetAnimation(Character* c) override;
	void Update(float deltatime) override;
	void HandleInput(float deltatime) override;

};
