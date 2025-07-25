#include "../headers/TransformState.h"


TransformState::TransformState(Character* character, CharacterStateType statetype, CharacterStateType previoustype) : CharacterState(character), statetype(statetype), previoustype(previoustype) {
	transformduration = 0.0f;
	elapsedTime = 0.0f;
	Singleton<AnimationManager>::getInstance().LoadAnimation("../Assets/Animation/TransformState.json", CharacterStateType::TransformState);
}

void TransformState::SetAnimation(Character* c) {
	if (character->getCharacterType() == CharacterType::Mario) {
		if (statetype == CharacterStateType::SuperState) {
			character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIO);

			character->animations[ActionState::Idle] = Singleton<AnimationManager>::getInstance().getAnimation(
				CharacterType::Mario,
				CharacterStateType::TransformState,
				ActionState::Idle
			);
			Singleton<SoundManager>::getInstance().play(SoundType::POWERUP);
		}
		else if (statetype == CharacterStateType::NormalState) {
			character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);
			if (previoustype == CharacterStateType::SuperState || previoustype == CharacterStateType::FireState) {

				character->animations[ActionState::Idle] = Singleton<AnimationManager>::getInstance().getAnimation(
					CharacterType::SmallCharacter,
					CharacterStateType::TransformState,
					ActionState::Idle
				);
			}
			Singleton<SoundManager>::getInstance().play(SoundType::PIPEDOWN);

		}

	}
	else if (character->getCharacterType() == CharacterType::Luigi) {
		if (statetype == CharacterStateType::SuperState) {
			character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIO);

			character->animations[ActionState::Idle] = Singleton<AnimationManager>::getInstance().getAnimation(
				CharacterType::Luigi,
				CharacterStateType::TransformState,
				ActionState::Idle
			);
			Singleton<SoundManager>::getInstance().play(SoundType::POWERUP);
		}
	}

	transformduration = character->animations[ActionState::Idle].durationtime * character->animations[ActionState::Idle].frame.size();
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->position.y = character->BasePosition - currentframe.height * character->scale;

}

void TransformState::Update(float deltatime) {
	elapsedTime += deltatime;

	if (transformduration != 0 && elapsedTime < transformduration) {
		Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
		character->position.y = character->BasePosition - currentframe.height * character->scale;
		character->animations[ActionState::Idle].Update(deltatime);
	}
	else {
		character->ChangeState(statetype, previoustype);
	}
}

CharacterStateType TransformState::getStateType() {
	return CharacterStateType::TransformState;
}
