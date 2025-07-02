#include "../headers/Mario.h"
#include "../headers/Global.h"
#include "../headers/Collision.h"
class Map;

Mario::Mario() {
	type = CharacterType::Mario;

	currentAction = ActionState::IDLE;
	// currentState = new NornmalState()
	currentdirection = Direction::Right;
	position = { 100, 100 };
}

Mario::Mario(Vector2 position) {
	type = CharacterType::Mario;

	currentAction = ActionState::IDLE;
	// currentState = new NornmalState()
	currentdirection = Direction::Right;
	this->position = position;
}

CharacterType Mario::getCharacterType() {
	return CharacterType::Mario;
}

