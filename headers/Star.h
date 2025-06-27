#pragma once
#include "Item.h"

class Star : public Item {
public: 
	Star() = default;
	Star(Vector2 v) : Item(v) {
		texture = LoadTexture("assets/ingame/Star.png");
		name = "Star";
	}
	void draw() override;
	void update() override;
	bool isCaught() override;
	bool used() override;
private:
};