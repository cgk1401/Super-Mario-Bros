#pragma once

#include "CharacterState.h"
#include "../headers/SuperState.h"

class TransformState : public CharacterState {
private:
	float transformduration; // thời gian chuyển giữa 2 state
	float elapsedTime;
	CharacterStateType statetype;
	CharacterStateType previoustype;

public:
	TransformState(Character* character, CharacterStateType statetype, CharacterStateType previoustype);
	~TransformState() override = default;

	void SetAnimation(Character* c) override;
	void Update(float deltatime) override;
	void HandleInput(float deltatime) override {}
	CharacterStateType getStateType() override;
};