#include "../headers/Luigi.h"

Luigi::Luigi() {
	type = CharacterType::Luigi;
	currentAction = ActionState::Idle;
	position = { 100, 300 };
	this->BasePosition = 300;
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;
}

Luigi::Luigi(Vector2 position) {
	type = CharacterType::Luigi;
	currentAction = ActionState::Idle;
	this->position = position;
	this->BasePosition = position.y;
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;
}

CharacterType Luigi::getCharacterType() {
	return CharacterType::Luigi;
}
