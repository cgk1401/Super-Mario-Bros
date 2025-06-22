#pragma once

#include "../headers/Character.h"
#include "../headers/InputHandler.h"
#include <map>
#include "raylib.h"

class Mario : public Character {
private:
	InputHandler inputHandler;
	float jumpTimeElapsed;
	float jumpDuration;
	bool isJumping;
public :
	Mario();
	Mario(Vector2 position);

	void Update(float deltatime, Map* map) override;
	void LoadSource() override;
	void Draw() override;
	void MoveLeft() override;
	void MoveRight() override;

};