#pragma once

#include <iostream>
#include <map>
#include "Animation.h"
#include "CharacterState.h"
#include "Global.h"
#include "OBSERVER/Subject.h"
using namespace std;

class CharacterState;
class NormalState;
class SuperState;
class TransformState;
class FireState;
class FireBall;
class StarmanState;

class Map;

class Character : public Subject {
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

	PhysicsConfig config;
	bool isJumpingUp = false;
	bool isGround = false;
	float jumpTimeElapsed = 0;
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
	void DIE(Enemy* e);
	void onDead();
	
	void Draw();
	void Update(float deltatime, bool applyPhysics = true);
	void HandleInput(float dt);

	void collectCoin();
	void breakBrick();
	void killEnemy(EnemyType type, Vector2 enemyPosition);
	void collectItem(ItemType type, Vector2 itemPosition);

	void moveRight(const float& speed = 2);
	void moveLeft(const float& speed = 2);
	void moveDown(const float& speed = 2); //flagpole only
};