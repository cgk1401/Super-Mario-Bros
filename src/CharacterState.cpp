#include "../Headers/CharacterState.h"
#include "../headers/Character.h"
#include <iostream>

CharacterState::CharacterState(Character* character) : character(character) {

}

float CharacterState::approach(float current, float target, float increase) {
	if (current < target) {
		return fmin(current + increase, target);
	}
	return fmax(current - increase, target);
}

Character* CharacterState::getCharacter() {
	{ return this->character; }
}

bool CharacterState::getIsGround() {
	return this->character->isGround;
}

void CharacterState::SetBasePosition(float newposition) {
	character->BasePosition = newposition;
}		