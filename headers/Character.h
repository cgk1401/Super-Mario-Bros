#pragma once

#include "Animation.h"
#include <map>
#include "CharacterState.h"
#include <iostream>

using namespace std;

class CharacterState;
class NormalState;

class Map;

enum class ActionState {
	IDLE,
	Run,
	Jump,
	Fall,
	DIE,
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

protected:
	Texture texture;
	map <ActionState, Animation> animations;
	Vector2 position;

	CharacterType type;
	CharacterState* currentState;
	ActionState currentAction;
	Direction currentdirection;

	float scale = 4.0f;

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