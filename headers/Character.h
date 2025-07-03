#pragma once

#include "Animation.h"
#include <map>
#include "CharacterState.h"
#include <iostream>

using namespace std;

class CharacterState;
class NormalState;
class SuperState;

class Map;

enum class ActionState {
	Idle,
	Run,
	Jump,
	Sit,
	Die,
};

enum class Direction {
	Left,
	Right
};

enum class CharacterType {
	Mario,
	Luigi,
};

class Character {
	friend class CharacterState;
	friend class NormalState;
	friend class SuperState;

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