#pragma once

#include <raylib.h>
#include "Animation.h"
using namespace std;

class VerticalLift {
private :
	Texture2D texture;
	Animation animations;
	Vector2 velocity;
	Vector2 position;
	Rectangle bound;

	const float speedY = 60.0f;
	const float scale = 3.0f;

	const float distance = 120.0f;
	float destinationBelow;
	float destinationAbove;
	bool moveingDown = true;

public :
	VerticalLift();
	VerticalLift(Vector2 position);

	~VerticalLift() { UnloadTexture(texture); }

	void LoadSource();
	void Update(float deltatime);
	void Draw();
	Rectangle getBound();
};