#pragma once

#include "Character.h"
#include <map>
#include <raylib.h>

class Mario : public Character {
public :
	Mario(Vector2 position);

	void Update(float deltatime) override;
	void LoadSource() override;
	void Draw() override;
	void MoveLeft() override;
	void MoveRight() override;

};