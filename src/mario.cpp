#include "../headers/Mario.h"
#include "../headers/Global.h"
#include "../headers/Collision.h"

class Map;

Mario::Mario() {
	type = CharacterType::Mario;
	currentAction = ActionState::Idle;
	position = { 100, 300 };
	this->BasePosition = 300;
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;
}

Mario::Mario(Vector2 position) {
	type = CharacterType::Mario;
	currentAction = ActionState::Idle;
	this->velocity = { 0, 0 };
	this->position = position;
	this->BasePosition = position.y;
	cout << 111111;
	currentState = new FireState(this);
	cout << 2222222;
	currentState->SetAnimation(this);
	cout << 33333;
	currentdirection = Direction::Right;
}

CharacterType Mario::getCharacterType() {
	return CharacterType::Mario;
}