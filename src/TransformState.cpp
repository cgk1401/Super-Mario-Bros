#include "../headers/TransformState.h"


TransformState::TransformState(Character* character, CharacterStateType statetype, CharacterStateType previoustype) : CharacterState(character), statetype(statetype), previoustype(previoustype) {
	transformduration = 0.0f;
	elapsedTime = 0.0f;
}

void TransformState::SetAnimation(Character* c) {
	if (character->getCharacterType() == CharacterType::Mario) {
		if (statetype == CharacterStateType::SuperState) {
			character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIO);

			Animation idle;

			idle.durationtime = 0.3f;
			idle.currenttime = 0.0f;
			idle.currentframe = 0;
			idle.frame.push_back({ 2, 88, 12, 16 });
			idle.frame.push_back({ 18, 80, 16, 24 });
			idle.frame.push_back({ 36, 72, 16, 32 });

			character->animations[ActionState::Idle] = idle;

		}
		else if (statetype == CharacterStateType::NormalState) {
			character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);
			if (previoustype == CharacterStateType::SuperState || previoustype == CharacterStateType::FireState) {
				Animation idle;

				idle.durationtime = 0.1f;
				idle.currenttime = 0.0f;
				idle.currentframe = 0;
				bool addframeabsent = false;
				for (int i = 0; i < 6; i++) {
					idle.frame.push_back(Rectangle{ float(233 + i * 17), 1, 16, 32 });
					idle.frame.push_back({ 318 ,34, 16, 16 });
				}

				for (int i = 0; i < 6; i++) {
					idle.frame.push_back(Rectangle{ float(233 + i * 17), 34, 16, 16 });
					idle.frame.push_back({ 318,34, 16, 16 });
				}

				character->animations[ActionState::Idle] = idle;
			}
		}

	}
	else if (character->getCharacterType() == CharacterType::Luigi) {
		if (statetype == CharacterStateType::SuperState) {
			Animation idle;

			idle.durationtime = 0.3f;
			idle.currenttime = 0.0f;
			idle.currentframe = 0;
			idle.frame.push_back({ 290, 88, 12, 16 });
			idle.frame.push_back({ 306, 80, 16, 24 });
			idle.frame.push_back({ 324, 72, 16, 32 });

			character->animations[ActionState::Idle] = idle;
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
