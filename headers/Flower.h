#pragma once
#include "Item.h"

class Flower : public Item {
public:
	Flower() = default;
	Flower(Vector2 v) : Item(v) {
		name = "Flower";
		texture = LoadTexture("../assets/ingame/Flower.png");
	}
	void draw() override;
	void update() override;
	bool isCaught() override;
	bool used() override;
private:
};