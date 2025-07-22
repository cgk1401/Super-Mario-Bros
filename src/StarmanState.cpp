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
	
	HandleInput(deltatime);
	
	// trạng thái đang rơi xuống

	if (currentTime >= duration) {
		//character->setActionState(ActionState::Idle);
		character->ChangeMiddleState(previousState);
		
	}
}

void StarmanState::HandleInput(float deltatime) {

	if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_DOWN)) {
		if (character->isGround) {
			// trạng thái đang ở trên mặt đất, nhấn KEY_P sẽ đặt trạng thái thành FlagpoleHold
			//if (IsKeyDown(KEY_P)) {
			//	character->setActionState(ActionState::FlagpoleHold);
			//}
			//else {
				// không bấm phím nào thì sẽ đặt trạng thái thành idle
				
			}
		}
	}

	// xử lý nhảy
	 //if (IsKeyPressed(KEY_SPACE) && isGround && character->currentAction != ActionState::Sit) {
	 //	character->velocity.y = config.JUMPFORCE;
	 //	isGround = false;
	 //	isJumpingUp = true;
	 //	jumpTimeElapsed = 0.0f;
	 //	character->setActionState(ActionState::Jump);
	 //}

	 //if (IsKeyDown(KEY_SPACE) && isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME) {
	 //	jumpTimeElapsed += deltatime;
	 //}
	 //else if (isJumpingUp && !IsKeyDown(KEY_SPACE)) {
	 //	isJumpingUp = false;
	 //}



CharacterStateType StarmanState::getStateType() {
	return CharacterStateType::StarmanState;
}
