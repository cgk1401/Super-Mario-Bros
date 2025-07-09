#pragma once

#include "CharacterState.h"
#include "Character.h"

class TransformState : public CharacterState {
private:
	float transformduration; // thời gian chuyển giữa 2 state
	float elapsedTime;
	CharacterTransformState transformstate;

public:
	TransformState(Character* character, CharacterTransformState transformstate);
	~TransformState() override = default;

	void SetAnimation(Character* c) override;
	void Update(float deltatime) override;
	void HandleInput(float deltatime) override {}
};