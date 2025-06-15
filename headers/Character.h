#pragma once

#include "Animation.h"
#include <map>

enum Actionstate {
	IDLE,
	Run,
	Jump,
	Fall,
	DIE,
};

class Character : public Animation{
protected:
	Texture2D texture{};
	std::map <Actionstate, Animation> animation;
	Actionstate currentstate = Actionstate::IDLE;
	Vector2 position = { 0,0 };
	float speed = 0.0f;

public:
	virtual void Update(float deltatime) = 0;
	virtual void Draw() = 0;
	virtual void LoadSource() = 0;
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;
};