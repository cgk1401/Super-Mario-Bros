#include "../Headers/CharacterState.h"
#include <iostream>

CharacterState::CharacterState(Character* character) : character(character) {

}

float CharacterState::approach(float current, float target, float increase) {
	if (current < target) {
		return fmin(current + increase, target);
	}
	return fmax(current - increase, target);
}
