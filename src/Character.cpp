#include "../headers/Character.h"
#include "../headers/Map.h"
#include <iostream>
using namespace std;

Character::~Character() {
	if (currentState) {
		delete currentState;
		currentState = nullptr;
	}
}

void Character::ChangeState(CharacterState* newState) {
	if (currentState) {
		delete currentState;
	}
	currentState = newState;
}

CharacterState* Character::GetCurrentState() const {
	return currentState;
}

void Character::setActionState(ActionState newActionState) {
	currentAction = newActionState;
}

void Character::setDirection(Direction newDirection) {
	currentdirection = newDirection;
}

void Character::Draw() {
	Rectangle currentframe = animations[currentAction].getcurrentframe();
	
	if (currentdirection == Direction::Right) {
		currentframe.width = abs(currentframe.width);
	}
	else if (currentdirection == Direction::Left) {
		currentframe.width = -abs(currentframe.width);
	}

	Rectangle destination = { position.x, position.y, currentframe.width * scale, currentframe.height * scale };

	DrawTexturePro(texture, currentframe, destination, { 0,0 }, 0, WHITE);
}

void Character::Update(float deltatime) {
	currentState->Update(deltatime);
}

