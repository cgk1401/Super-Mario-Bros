#include "../headers/Mario.h"
#include "../headers/Global.h"
#include "../headers/Collision.h"

class Map;

Mario::Mario() {
	type = CharacterType::Mario;
	currentAction = ActionState::Run;
	position = { 100, 300 };
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;
}

Mario::Mario(Vector2 position) {
	type = CharacterType::Mario;
	currentAction = ActionState::Run;
	this->position = position;
	currentState = new NormalState(this);
	currentState->SetAnimation(this);
	currentdirection = Direction::Right;
}

CharacterType Mario::getCharacterType() {
	return CharacterType::Mario;
}

