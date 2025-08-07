#pragma once

#include "Animation.h"
#include <raylib.h>
using namespace std;

class BowserFireBall {
	friend class Collision;
private :
	Texture texture;
	Animation animations;
	Vector2 position;
	Vector2 velocity;
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

	void Update(float deltatime);
	void LoadSource();
	Rectangle getBound();
	void Draw();

	bool getIsActive();
	void ActiveStatus();
	void Deactive();

};