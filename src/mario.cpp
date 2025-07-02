#include "../headers/Mario.h"
#include "../headers/Global.h"
#include "../headers/Collision.h"
class Map;

Mario::Mario() {
	type = CharacterType::Mario;
	currentAction = ActionState::Run;
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;

	position = { 100, 300 };
}

Mario::Mario(Vector2 position) {
	type = CharacterType::Mario;
	currentAction = ActionState::Run;
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;

	this->position = position;
}

CharacterType Mario::getCharacterType() {
	return CharacterType::Mario;
}

