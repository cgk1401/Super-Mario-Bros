#pragma once

#include "CharacterState.h"

class NormalState : public CharacterState {
private :
	PhysicsConfig config;
public :
	NormalState(Character* character);
	~NormalState() override = default;

	void SetAnimation(Character* c) override;
	void Update(float deltatime) override;
	void HandleInput(float deltatime) override;
};