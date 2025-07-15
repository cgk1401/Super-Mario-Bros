#pragma once

#include <iostream>
#include <map>
#include "Animation.h"
#include "CharacterState.h"
#include "Global.h"

using namespace std;

class CharacterState;
class NormalState;
class SuperState;
class TransformState;
class FireState;
class FireBall;
class StarmanState;

class Map;

class Character {
	friend class Collision;
	friend class CharacterState;
	friend class NormalState;
	friend class SuperState;
	friend class TransformState;
	friend class FireState;
	friend class FireBall;
	friend class StarmanState;

protected:
	Texture texture;
	map <ActionState, Animation> animations;
	Vector2 position;
	Vector2 velocity = { 0,0 };

	CharacterType type;
	CharacterState* currentState;
	ActionState currentAction;
	Direction currentdirection;

	float scale = 4.0f;
	float BasePosition;

public:
	virtual ~Character();

	void ChangeState(CharacterStateType newState, CharacterStateType previousState);
	void ChangeMiddleState(CharacterStateType newState);
	CharacterState* GetCurrentState() const;
	virtual CharacterType getCharacterType() = 0;
	void setActionState(ActionState newActionState);
	void setDirection(Direction newDirection);
	Rectangle getBound() const;
	Rectangle getFootSensor() const;
	ActionState getCurrentAction() const;
	CharacterStateType getCharacterStateType() const;
	void DIE();

	void Draw();
	void Update(float deltatime);
};