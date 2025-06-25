#pragma once
#include "Item.h"

class Star : public Item {
public: 
	void draw() override;
	void update() override;
	bool isCaught() override;
	bool used() override;
private:
};