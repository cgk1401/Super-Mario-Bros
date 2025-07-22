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
	HandleInput(deltatime);
}

void NormalState::HandleInput(float deltatime) {
}

CharacterStateType NormalState::getStateType() {
	return CharacterStateType::NormalState;
}

