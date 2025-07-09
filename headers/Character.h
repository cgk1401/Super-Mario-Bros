#pragma once

#include <iostream>
#include <map>
#include "Animation.h"
#include "CharacterState.h"
#include "FireState.h"

using namespace std;

class CharacterState;
class NormalState;
class SuperState;
class TransformState;
class FireState;
class FireBall;

class Map;

enum class ActionState {
	Idle,
	Run,
	Jump,
	Sit,
	Die,
	FlagpoleHold,
	Fireball,
};

// class Character {
// protected:
// 	Texture2D texture;
// 	std::map <Actionstate, Animation> animation;
// 	Actionstate currentstate = Actionstate::IDLE;
// 	Vector2 position = { 0,0 };
// 	const float speed = 2;

// 	const float gravity;
enum class Direction {
	Left,
	Right
};

enum class CharacterType {
	Mario,
	Luigi,
};

enum class CharacterTransformState {
	Super,
};

class Character {
	friend class CharacterState;
	friend class NormalState;
	friend class SuperState;
	friend class TransformState;
	friend class FireState;
	friend class FireBall;

protected:
	Texture texture;
	map <ActionState, Animation> animations;
	Vector2 position;
	Vector2 velocity;

	CharacterType type;
	CharacterState* currentState;
	ActionState currentAction;
	Direction currentdirection;

	float scale = 3.0f;
	float BasePosition;

public:
	virtual ~Character();

	void ChangeState(CharacterState* newState);
	CharacterState* GetCurrentState() const;
	virtual CharacterType getCharacterType() = 0;
	void setActionState(ActionState newActionState);
	void setDirection(Direction newDirection);

	void Draw();
	void Update(float deltatime);
};