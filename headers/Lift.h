#pragma once

#include "Animation.h"
#include <raylib.h>

using namespace std;

class Lift {
protected:
	Texture2D texture;
	Animation animations;
	Vector2 velocity;
	Vector2 position;
	Rectangle bound;

public :
	Lift() : texture{ 0 }, 
		animations{}, 
		velocity{ 0.0f, 0.0f }, 
		position{ 0.0f, 0.0f },
		bound{ 0.0f, 0.0f, 0.0f, 0.0f } 
	{};

	Lift(Vector2 position) : texture{ 0 },
		animations{},
		velocity{ 0.0f, 0.0f },
		position (position),
		bound{ 0.0f, 0.0f, 0.0f, 0.0f } 
	{};

	virtual ~Lift() { UnloadTexture(texture); }

	virtual void LoadSource() = 0;
	virtual void Update(float deltatime) = 0;
    virtual void Draw() = 0;
    virtual Rectangle getBound() = 0;
	virtual Vector2 getVelocity() {
		return this->velocity;
	}
};