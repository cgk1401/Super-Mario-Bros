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
	if (currentAction == ActionState::Idle) {
		if (currentState) {
			delete currentState;
		}
		currentState = newState;
		currentAction = ActionState::Idle;
		currentState->SetAnimation(this);
	}
}

CharacterState* Character::GetCurrentState() const {
	return currentState;
}

void Character::setActionState(ActionState newActionState) {
	if (currentAction != newActionState) {
		currentAction = newActionState;
		animations[currentAction].reset();
		//Rectangle currentframe = animations[currentAction].getcurrentframe();
		//position.y = BasePosition - currentframe.height * scale;
	}
}

void Character::setDirection(Direction newDirection) {
	currentdirection = newDirection;
}
Rectangle Character::getBound() const {
    Rectangle frame = animations.at(currentAction).getcurrentframe();
	
    return {
        position.x,
        position.y,
        frame.width * scale,
        frame.height * scale
    };
}

ActionState Character::getCurrentAction() const{
	return currentAction;
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

	FireState* firestate = dynamic_cast <FireState*> (currentState);
	if (firestate) {
		for (int i = 0; i < firestate->getFireBall().size(); i++) {
			if (firestate->getFireBall()[i]->isActive) {
				firestate->getFireBall()[i]->Draw(firestate->getCharacter());
			}
		}
	}

}

void Character::Update(float deltatime) {
	currentState->Update(deltatime);
}

