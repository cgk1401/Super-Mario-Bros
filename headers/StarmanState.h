#pragma once

#include "CharacterState.h"
#include "../headers/Character.h"
#include "../headers/TextureManager.h"
#include "../headers/Collision.h"
#include "../headers/SoundManager.h"

class StarmanState : public CharacterState {
private:
	PhysicsConfig config;
	CharacterStateType previousState;
	const float duration = 5.0f;
	float currentTime = 0.0f;

public:
	StarmanState(Character* character, CharacterStateType previousState);
	~StarmanState() override;

	void SetAnimation(Character* c) override;
	void Update(float deltatime) override;
	void HandleInput(float deltatime) override;
	CharacterStateType getStateType() override;
};


