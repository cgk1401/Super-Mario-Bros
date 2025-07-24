#pragma once

#include "CharacterState.h"
#include "../headers/Character.h"
#include "../headers/SuperState.h"
#include "../headers/TransformState.h"
#include "../headers/TextureManager.h"
#include "../headers/Collision.h"
#include "../headers/SoundManager.h"

class NormalState : public CharacterState {
private :
	PhysicsConfig config;
public :
	NormalState(Character* character);
	~NormalState() override = default;

	void SetAnimation(Character* c) override;
	void Update(float deltatime) override;
	void HandleInput(float deltatime) override;
	CharacterStateType getStateType() override;
};