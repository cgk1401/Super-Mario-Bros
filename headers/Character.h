#pragma once

#include <iostream>
#include <map>
#include "Animation.h"
#include "CharacterState.h"
#include "Global.h"
#include "OBSERVER/Subject.h"
#include "GameObject.h"
using namespace std;

class CharacterState;
class NormalState;
class SuperState;
class TransformState;
class FireState;
class FireBall;
class StarmanState;

class Map;

class Character : public GameObject, public Subject {
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
	CharacterType type;
	CharacterState* currentState;
	ActionState currentAction;
	Direction currentdirection;

	float scale = 4.0f;
	float BasePosition;

	PhysicsConfig config;
	bool isJumpingUp = false;
	float jumpTimeElapsed = 0;

public:
	bool isControlled = false; 

	virtual ~Character();

	void ChangeState(CharacterStateType newState, CharacterStateType previousState);
	void ChangeMiddleState(CharacterStateType newState);
	CharacterState* GetCurrentState() const;
	virtual CharacterType getCharacterType() = 0;
	void setActionState(ActionState newActionState);
	void setDirection(Direction newDirection);
	ActionState getCurrentAction() const;
	CharacterStateType getCharacterStateType() const;
	void DIE(Enemy* e);
	void onDead();

	void collectCoin();
	void breakBrick();
	void killEnemy(EnemyType type, Vector2 enemyPosition);
	void collectItem(ItemType type, Vector2 itemPosition);

	void moveRight(const float& speed = 2);
	void moveLeft(const float& speed = 2);
	void moveDown(const float& speed = 2); //flagpole only
	void setPosition(Vector2 newPosition);
	Vector2 getPosition();

	void HandleInput(float dt);
	//Inherit GameObject methods
	void draw() override;
	void update(float deltatime) override;
	Rectangle getBound() const override;
	ObjectType getObjectType() const override;

	void onFootCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override;
	void onGeneralCollision(Direction collideSide, Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override;
    void onHeadCollision(Tile& tile, int row, int col, Map* map, MapTileInstance* tileInstance) override;
    void onCollideWith(GameObject* object) override;
};