#pragma once

#include "Animation.h"
#include "Item.h"
#include <raylib.h>
using namespace std;

class BowserFireBall : public Item {
private :
	Animation animations;
	const float scale = 3.0f;

	float positionDestinationY;
	const float speedX = 200.0f;
	const float speedY = 250.0f;
	bool isBelow;

	bool isActive = true;

public :
	BowserFireBall();
	BowserFireBall(Vector2 position, float positionDestinationY);
	~BowserFireBall();

	void update(float deltatime) override;
	void LoadSource();
	void draw() override;

	bool getIsActive();
	void ActiveStatus();
	void Deactive();

	void OnCollected(Character* player) override;
    Rectangle getBound() const override;
};