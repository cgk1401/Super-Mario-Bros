#pragma once

#include "Animation.h"
#include <map>

enum class Actionstate {
	IDLE,
	Run,
	Jump,
	Fall,
	DIE,
};

class Character : public Animation{
protected:
	Texture2D texture;
	std::map <Actionstate, Animation> animation;
	Actionstate currentstate = Actionstate::IDLE;
	Vector2 position;

public:
	virtual void Update(float deltatime) = 0;
	virtual void Draw() = 0;
	virtual void LoadSource() = 0;

};