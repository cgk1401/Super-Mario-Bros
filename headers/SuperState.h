#pragma once

#include "CharacterState.h"
#include "../headers/FireState.h"
#include "../headers/Character.h"
#include "../headers/TextureManager.h"

class SuperState : public CharacterState {
private:
	PhysicsConfig config;
public:
	SuperState(Character* character);
	~SuperState() override = default;

	void SetAnimation(Character* c) override;
	void Update(float deltatime) override;
	void HandleInput(float deltatime) override;
	CharacterStateType getStateType() override;
};
