#include "../headers/Character.h"
#include "../headers/Map.h"
#include "../headers/NormalState.h"
#include "../headers/SuperState.h"
#include "../headers/StarmanState.h"
#include "../headers/FireState.h"
#include "../headers/EffectManager.h"
#include "../headers/TransformState.h"
#include "../headers/Enemy.h"
#include <iostream>
using namespace std;

Character::~Character() {
	if (currentState) {
		delete currentState;
		currentState = nullptr;
	}
}
void Character::collectCoin(){
	notify(EventType::COIN_COLLECT);
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
	float delta = 4.0f; //narrow the width of player
    return {
        position.x + delta,
        position.y,
        frame.width * scale - delta * 2,
        frame.height * scale
    };
}


Rectangle Character::getFootSensor() const {
	Rectangle bound = getBound();
	float width = bound.width - 6.0f;
	float height = 4;

	return{
		bound.x + 3.0f,
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

	//DrawRectangleLinesEx(getBound(), 0.4f, RED);

}
void Character::HandleInput(float deltatime) {
	float targetspeed = IsKeyDown(KEY_LEFT_CONTROL) ? config.MAX_SPEED : config.SPEED;
	float acc = config.ACCELERATION;

	if (IsKeyDown(KEY_RIGHT)) {
		if (velocity.x < 0) acc *= 3.0f; // tăng gia tốc khi đổi hướng
		velocity.x = approach(velocity.x, targetspeed, acc * deltatime);
		setActionState(ActionState::Run);
		setDirection(Direction::Right);
	}
	else if (IsKeyDown(KEY_LEFT)) {
		if (velocity.x > 0) acc *= 3.0f;
		velocity.x = approach(velocity.x, -targetspeed, acc * deltatime);
		setActionState(ActionState::Run);
		setDirection(Direction::Left);
	}

	if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
		if (isGround) {
			velocity.x = 0.0f;
			setActionState(ActionState::Idle);
		}
	}

	//if (IsKeyDown(KEY_SPACE)) {
	//	if (isGround) Singleton<SoundManager>::getInstance().play(SoundType::JUMP);
	//}
	 //xử lý nhảy
	 if (IsKeyPressed(KEY_SPACE) && isGround) {
		velocity.y = config.JUMPFORCE;
		isGround = false;
		isJumpingUp = true;
		jumpTimeElapsed = 0.0f;
		setActionState(ActionState::Jump);
		Singleton<SoundManager>::getInstance().play(SoundType::JUMP);
	 }

	 if (IsKeyDown(KEY_SPACE) && isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME && !isGround) {
		jumpTimeElapsed += deltatime;
	 }
	 else if (isJumpingUp && !IsKeyDown(KEY_SPACE)) {
		isJumpingUp = false;
	 }
	 /*
	if (IsKeyDown(KEY_SPACE)) {
		if (isGround) {
			if(getCharacterStateType() == CharacterStateType::NormalState)
				Singleton<SoundManager>::getInstance().play(SoundType::JUMP_SMALL);
			else  Singleton<SoundManager>::getInstance().play(SoundType::JUMP);
			velocity.y = config.JUMPFORCE;
			isGround = false;
			isJumpingUp = true;
			jumpTimeElapsed = 0.0f;
		}
		else if (isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME && !isGround) {
			jumpTimeElapsed += deltatime;
			velocity.y = config.JUMPFORCE;  // hoặc scale theo thời gian
			//cout << "is jumpin\n";
		}
	}
	else {
		isJumpingUp = false;
	}
	*/
}
void Character::Update(float deltatime) {
	currentState->Update(deltatime);
	//DO NOT UPDATE WHEN MARIO IS TRANSFORMING
	if (currentState->getStateType() == CharacterStateType::TransformState) return;

		animations[currentAction].Update(deltatime);
	// cập nhật Baseposition
	Rectangle currentframe = animations[currentAction].getcurrentframe();
	BasePosition = position.y +  currentframe.height * scale;

	HandleInput(deltatime);
	if (!isGround) {
		if (isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME && IsKeyDown(KEY_SPACE)) {
			velocity.y += config.GRAVITY * 0.1f * deltatime; // Trọng lực nhẹ hơn khi giữ phím nhảy
		}
		else {
			velocity.y += config.GRAVITY * deltatime; // Trọng lực bình thường khi không giữ hoặc hết thời gian tối đa
		
		}
		if(isJumpingUp) setActionState(ActionState::Jump);
	}
	else {
		//cout << "on ground\n";
		velocity.y = 0; 
		isJumpingUp = false;
		if (fabs(velocity.x) < 0.1f) {
			if (IsKeyDown(KEY_P)) {
				setActionState(ActionState::FlagpoleHold);
			} 
		} 
	}

	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;

	if(position.y > screenHeight + 10) onDead();
}
void Character::onDead(){
	Singleton<EffectManager>::getInstance().marioDead(this->position, texture, animations[ActionState::Die].getcurrentframe());
	Singleton<SoundManager>::getInstance().play(SoundType::DIE);
	currentAction = ActionState::Die;
	notify(EventType::ON_DEATH);
}
void Character::DIE(Enemy* e){
	if(currentAction == ActionState::Die) return;
	
	if(getCharacterStateType() == CharacterStateType::NormalState){
		onDead();
	}
	else if(getCharacterStateType() == CharacterStateType::SuperState || getCharacterStateType() == CharacterStateType::FireState){
		//TRANSFORM GRADUALLY TO NORMAL STATE
		ChangeMiddleState(CharacterStateType::NormalState);
	}
	else if (getCharacterStateType() == CharacterStateType::StarmanState) {
		e->onDeath(DeathType::FALLING);
	}
}

void Character::breakBrick(){
	notify(EventType::BRICK_BREAK);
}

void Character::killEnemy(EnemyType type, Vector2 enemyPosition){
	if(type == EnemyType::GOOMBA) notify(EventType::ENEMY_KILL_GOOMBA, &enemyPosition);
	else if(type == EnemyType::KOOPA) notify(EventType::ENEMY_KILL_KOOPA, &enemyPosition);
}

void Character::collectItem(ItemType type, Vector2 itemPosition)
{
	if (type == ItemType::MUSHROOM) notify(EventType::POWERUP_COLLECT_MUSHROOM, &itemPosition);
	else if (type == ItemType::FLOWER) notify(EventType::POWERUP_COLLECT_FLOWER, &itemPosition);
	else if (type == ItemType::STAR) notify(EventType::POWERUP_COLLECT_STAR, &itemPosition);
	else if (type == ItemType::COIN) notify(EventType::COIN_COLLECT, &itemPosition);
}
