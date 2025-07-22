#include "../Headers/NormalState.h"
#include <raylib.h>

NormalState::NormalState(Character* character) : CharacterState(character){
	character->velocity = { 0, 0 };
	Singleton<AnimationManager>::getInstance().LoadAnimation("../Assets/Animation/NormalState.json", CharacterStateType::NormalState);
}

void NormalState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);

		character->animations[ActionState::Idle] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::NormalState,
			ActionState::Idle
		);

		character->animations[ActionState::Run] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::NormalState,
			ActionState::Run
		);

		character->animations[ActionState::Jump] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::NormalState,
			ActionState::Jump
		);

		character->animations[ActionState::Die] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::NormalState,
			ActionState::Die
		);

		character->animations[ActionState::FlagpoleHold] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::NormalState,
			ActionState::FlagpoleHold
		);

	}
	else if (c->getCharacterType() == CharacterType::Luigi) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);

		character->animations[ActionState::Idle] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Luigi,
			CharacterStateType::NormalState,
			ActionState::Idle
		);

		character->animations[ActionState::Run] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Luigi,
			CharacterStateType::NormalState,
			ActionState::Run
		);

		character->animations[ActionState::Jump] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Luigi,
			CharacterStateType::NormalState,
			ActionState::Jump
		);

		character->animations[ActionState::Die] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Luigi,
			CharacterStateType::NormalState,
			ActionState::Die
		);

		character->animations[ActionState::FlagpoleHold] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Luigi,
			CharacterStateType::NormalState,
			ActionState::FlagpoleHold
		);

	}
	// cập nhật Baseposition
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->BasePosition += currentframe.height * character->scale;
}

void NormalState::Update(float deltatime) {
	character->animations[character->currentAction].Update(deltatime);
	// cập nhật Baseposition
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->BasePosition = character->position.y +  currentframe.height * character->scale;

	HandleInput(deltatime);
	if (!isGround) {
		if (isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME && IsKeyDown(KEY_SPACE)) {
			character->velocity.y += config.GRAVITY * 0.1f * deltatime; // Trọng lực nhẹ hơn khi giữ phím nhảy
			//cout << "not on ground 1\n";
		}
		else {
			character->velocity.y += config.GRAVITY * deltatime; // Trọng lực bình thường khi không giữ hoặc hết thời gian tối đa
			//cout << "not on ground 2\n";
		}
		if(isJumpingUp) character->setActionState(ActionState::Jump);
	}
	else {
		//cout << "on ground\n";
		character->velocity.y = 0; 
		isJumpingUp = false;
		if (fabs(character->velocity.x) < 0.1f) {
			if (IsKeyDown(KEY_P)) {
				character->setActionState(ActionState::FlagpoleHold);
			}
		} 
	}

	character->position.x += character->velocity.x * deltatime;
	character->position.y += character->velocity.y * deltatime;
}

void NormalState::HandleInput(float deltatime) {
	float targetspeed = IsKeyDown(KEY_LEFT_CONTROL) ? config.MAX_SPEED : config.SPEED;
	float acc = config.ACCELERATION;

	if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)) {
		if (character->velocity.x < 0) acc *= 3.0f; // tăng gia tốc khi đổi hướng
		character->velocity.x = approach(character->velocity.x, targetspeed, acc * deltatime);
		character->setActionState(ActionState::Run);
		character->setDirection(Direction::Right);
	}
	else if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
		if (character->velocity.x > 0) acc *= 3.0f;
		character->velocity.x = approach(character->velocity.x, -targetspeed, acc * deltatime);
		character->setActionState(ActionState::Run);
		character->setDirection(Direction::Left);
	}

	if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
		if (isGround) {
			character->velocity.x = 0.0f;
			character->setActionState(ActionState::Idle);
		}
	}
	

	if (IsKeyDown(KEY_SPACE)) {
		if (isGround) {
			Singleton<SoundManager>::getInstance().play(SoundType::JUMP_SMALL);
			character->velocity.y = config.JUMPFORCE;
			isGround = false;
			isJumpingUp = true; 
			jumpTimeElapsed = 0.0f;
		}
		else if (isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME && !isGround) {
			jumpTimeElapsed += deltatime;
			character->velocity.y = config.JUMPFORCE;  // hoặc scale theo thời gian
			//cout << "is jumpin\n";
		}
	} else {
		isJumpingUp = false;
	}
}

CharacterStateType NormalState::getStateType() {
	return CharacterStateType::NormalState;
}

