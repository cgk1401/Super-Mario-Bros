#include "../headers/Luigi.h"

Luigi::Luigi() {
	type = CharacterType::Luigi;
	currentAction = ActionState::IDLE;
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;

	position = { 100, 300 };
}

Luigi::Luigi(Vector2 position) {
	type = CharacterType::Luigi;
	currentAction = ActionState::IDLE;
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;

	this->position = position;
}

CharacterType Luigi::getCharacterType() {
	return CharacterType::Luigi;
}
