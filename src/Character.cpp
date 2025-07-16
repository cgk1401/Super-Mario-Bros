#include "../headers/Character.h"
#include "../headers/Map.h"
#include "../headers/NormalState.h"
#include "../headers/SuperState.h"
#include "../headers/StarmanState.h"
#include "../headers/FireState.h"
#include "../headers/EffectManager.h"

#include <iostream>
using namespace std;

Character::~Character() {
	if (currentState) {
		delete currentState;
		currentState = nullptr;
	}
}

void Character::ChangeState(CharacterStateType newState, CharacterStateType previosState) {
	if (currentState) {
		delete currentState;
	}
	switch (newState)
	{
	case CharacterStateType::NormalState:
		currentState = new NormalState(this);
		break;
	case CharacterStateType::SuperState:
		currentState = new SuperState(this);
		break;
	case CharacterStateType::FireState:
		currentState = new FireState(this);
		break;
	case CharacterStateType::StarmanState:
		currentState = new StarmanState(this, previosState);
		break;
	default:
		break;
	}
	currentState->SetAnimation(this);
}

void Character::ChangeMiddleState(CharacterStateType newState) {
	CharacterStateType currentstatetype = currentState->getStateType();
	if (currentState) {
		delete currentState;
	}
	currentState = new TransformState(this, newState, currentstatetype);
	currentAction = ActionState::Idle;
	currentState->SetAnimation(this);
}

CharacterState* Character::GetCurrentState() const {
	return currentState;
}

void Character::setActionState(ActionState newActionState) {
	if (currentAction != newActionState) {
		//avoid conflict between 2 frames if they are different of size
		Vector2 prevFrame = {animations[currentAction].getcurrentframe().width, animations[currentAction].getcurrentframe().height};
		Vector2 newFrame = {animations[newActionState].getcurrentframe().width, animations[newActionState].getcurrentframe().height};
		float heightDiff = prevFrame.y - newFrame.y;
		float widthDiff = prevFrame.x - newFrame.x;
		position.y += heightDiff * scale;
		//position.x += widthDiff * scale;

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


Rectangle Character::getFootSensor() const {
	Rectangle bound = getBound();
	float width = bound.width - 10;
	float height = 4;

	return{
		bound.x + 5,
		bound.y + bound.height - height / 2,
		width,
		height
	};
}
ActionState Character::getCurrentAction() const{
	return currentAction;
}

CharacterStateType Character::getCharacterStateType() const{
	return currentState->getStateType();
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

	DrawRectangleRec(getFootSensor(), RED);
}

void Character::Update(float deltatime) {
	currentState->Update(deltatime);
}

void Character::DIE(){
	if(currentAction == ActionState::Die) return;
	
	if(getCharacterStateType() == CharacterStateType::NormalState){
		currentAction = ActionState::Die;
		EffectManager::get().marioDead(this->position, texture, animations[ActionState::Die].getcurrentframe());
	}
	else if(getCharacterStateType() == CharacterStateType::SuperState || getCharacterStateType() == CharacterStateType::FireState){
		//TRANSFORM GRADUALLY TO NORMAL STATE
	}
}