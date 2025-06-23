#pragma once

#include "../headers/Character.h"
#include "../headers/InputHandler.h"
#include <map>
#include "raylib.h"

enum class Direction {
	LEFT,
	RIGHT
};

class Mario : public Character {
private:
	InputHandler inputHandler;
	Direction currentDirection;
	float jumpTimeElapsed;
	float jumpDuration;

	const float maxSpeed = 3.5;
	const float acceleration = 8; 
	const float friction = 5;
public :
	Mario();
	Mario(Vector2 position);

	void Update(float deltatime, Map* map) override;
	void LoadSource() override;
	void Draw() override;
	void MoveLeft() override;
	void MoveRight() override;

};