#include "../headers/Luigi.h"

Luigi::Luigi() {
	type = CharacterType::Luigi;

	currentAction = ActionState::IDLE;
	// currentState = new NornmalState()
	currentdirection = Direction::Right;
	position = { 100, 100 };
}

Luigi::Luigi(Vector2 position) {
	type = CharacterType::Luigi;

	currentAction = ActionState::IDLE;
	// currentState = new NornmalState()
	currentdirection = Direction::Right;
	this->position = position;
}

CharacterType Luigi::getCharacterType() {
	return CharacterType::Luigi;
}
