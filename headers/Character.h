#pragma once

#include "Animation.h"
#include <map>
class Map;

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
	const float speed = 2;

	const float gravity;
	Vector2 velocity;
	float scale;
	Rectangle bound;

	bool onGround;
	bool isJumpingUp;

public:
	Character();
	//virtual ~Character();
	friend class Collision;

	virtual void Update(float deltatime, Map* map) = 0;
	virtual void Draw() = 0;
	virtual void LoadSource() = 0;
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;
	virtual void handleCollision(Map* map);
	virtual Vector2 getPos();
};