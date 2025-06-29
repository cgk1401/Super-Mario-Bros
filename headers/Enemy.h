#pragma once
#include "Animation.h"

class Enemy {
protected :
	Vector2 position;
	Rectangle bound;
	Texture texture;
public :
	Enemy() : position({0,0}), bound({0,0,0,0}), texture({0}){}
	virtual ~Enemy() = default;
	virtual void Update(float deltatime) = 0;
	virtual void Draw() = 0;
	virtual void LoadSource() = 0;
};