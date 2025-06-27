#pragma once
#include "Item.h"

class Mushroom : public Item {
public:
	Mushroom() = default;
	Mushroom(Vector2 v);
	void draw() override;
	void update() override;
	bool isCaught() override;
	bool used() override;
private:
};
