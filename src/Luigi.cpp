#include "../headers/Luigi.h"

Luigi::Luigi() {
	type = CharacterType::Luigi;
	currentAction = ActionState::IDLE;
	position = { 100, 300 };
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;
}

Luigi::Luigi(Vector2 position) {
	type = CharacterType::Luigi;
	currentAction = ActionState::IDLE;
	this->position = position;
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;
}

CharacterType Luigi::getCharacterType() {
	return CharacterType::Luigi;
}
