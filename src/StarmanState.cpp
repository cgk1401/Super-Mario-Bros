#include "../headers/StarmanState.h"

StarmanState::StarmanState(Character* character, CharacterStateType previousState) : CharacterState(character) {
	this->previousState = previousState;
	Singleton<SoundManager>::getInstance().playMusic(MusicType::STARMAN, true);
	Singleton<AnimationManager>::getInstance().LoadAnimation("../Assets/Animation/StarmanState.json", CharacterStateType::StarmanState);
}

StarmanState::~StarmanState() {
	Singleton<SoundManager>::getInstance().stopMusic();
}

void StarmanState::SetAnimation(Character* c) {
	if (previousState == CharacterStateType::NormalState) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);

		character->animations[ActionState::Idle] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::SmallCharacter,
			CharacterStateType::StarmanState,
			ActionState::Idle
		);

		character->animations[ActionState::Run] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::SmallCharacter,
			CharacterStateType::StarmanState,
			ActionState::Run
		);

		character->animations[ActionState::Jump] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::SmallCharacter,
			CharacterStateType::StarmanState,
			ActionState::Jump
		);

		character->animations[ActionState::Die] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::SmallCharacter,
			CharacterStateType::StarmanState,
			ActionState::Die
		);

		character->animations[ActionState::FlagpoleHold] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::SmallCharacter,
			CharacterStateType::StarmanState,
			ActionState::FlagpoleHold
		);
	}

	else if (previousState == CharacterStateType::SuperState || previousState == CharacterStateType::FireState) {
		// Frame Mario lớn hơn
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);

		character->animations[ActionState::Idle] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::BigCharacter,
			CharacterStateType::StarmanState,
			ActionState::Idle
		);

		character->animations[ActionState::Run] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::BigCharacter,
			CharacterStateType::StarmanState,
			ActionState::Run
		);

		character->animations[ActionState::Jump] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::BigCharacter,
			CharacterStateType::StarmanState,
			ActionState::Jump
		);

		character->animations[ActionState::Sit] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::BigCharacter,
			CharacterStateType::StarmanState,
			ActionState::Sit
		);

		character->animations[ActionState::FlagpoleHold] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::BigCharacter,
			CharacterStateType::StarmanState,
			ActionState::FlagpoleHold
		);
	}

	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->position.y = character->BasePosition - currentframe.height * character->scale;
}

void StarmanState::Update(float deltatime) {
	currentTime += deltatime;
	character->animations[character->currentAction].Update(deltatime);
	Singleton<SoundManager>::getInstance().updateMusic();

	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->BasePosition = character->position.y + currentframe.height * character->scale;

	HandleInput(deltatime);
	if (!isGround) {
		if (isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME && IsKeyDown(KEY_SPACE)) {
			character->velocity.y += config.GRAVITY * 0.1f * deltatime; // Trọng lực nhẹ hơn khi giữ phím nhảy
		}
		else {
			character->velocity.y += config.GRAVITY * deltatime; // Trọng lực bình thường khi không giữ hoặc hết thời gian tối đa
		}
		if (isJumpingUp) character->setActionState(ActionState::Jump);
	}
	else {
		if (fabs(character->velocity.x) < 0.1f) {
			if (IsKeyDown(KEY_P)) {
				character->setActionState(ActionState::FlagpoleHold);
			}
		}
	}

	character->position.x += character->velocity.x * deltatime;
	character->position.y += character->velocity.y * deltatime;

	// trạng thái đang rơi xuống
}

void StarmanState::HandleInput(float deltatime) {
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

	if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_DOWN)) {
		if (isGround) {
			// trạng thái đang ở trên mặt đất, nhấn KEY_P sẽ đặt trạng thái thành FlagpoleHold
			//if (IsKeyDown(KEY_P)) {
			//	character->setActionState(ActionState::FlagpoleHold);
			//}
			//else {
				// không bấm phím nào thì sẽ đặt trạng thái thành idle
				character->velocity.x = 0.0f;
				character->setActionState(ActionState::Idle);
			//}
		}
	}

	if (IsKeyDown(KEY_SPACE)) {
		if (isGround) {
			Singleton<SoundManager>::getInstance().play(SoundType::JUMP);
			character->velocity.y = config.JUMPFORCE;
			isGround = false;
			isJumpingUp = true;
			jumpTimeElapsed = 0.0f;
		}
		else if (isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME) {
			jumpTimeElapsed += deltatime;
			character->velocity.y = config.JUMPFORCE;  // hoặc scale theo thời gian
		}
	}
	else {
		isJumpingUp = false;
	}
}

CharacterStateType StarmanState::getStateType() {
	return CharacterStateType::StarmanState;
}
