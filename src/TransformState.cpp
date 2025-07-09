#include "../headers/TransformState.h"
#include "../headers/SuperState.h"


TransformState::TransformState(Character* character, CharacterTransformState transformstate) : CharacterState(character) {
	transformduration = 0.0f;
	elapsedTime = 0.0f;
	this->transformstate = transformstate;
}

void TransformState::SetAnimation(Character* c) {
	if (character->getCharacterType() == CharacterType::Mario) {
		if (transformstate == CharacterTransformState::Super) {

			Animation idle;

			idle.durationtime = 0.3f;
			idle.currenttime = 0.0f;
			idle.currentframe = 0;
			idle.frame.push_back({ 2, 88, 12, 16 });
			idle.frame.push_back({ 18, 80, 16, 24 });
			idle.frame.push_back({ 36, 72, 16, 32 });

			character->animations[ActionState::Idle] = idle;
			transformduration = character->animations[ActionState::Idle].durationtime * character->animations[ActionState::Idle].frame.size();

		}

	}
	else if (character->getCharacterType() == CharacterType::Luigi) {
		if (transformstate == CharacterTransformState::Super) {
			Animation idle;

			idle.durationtime = 0.3f;
			idle.currenttime = 0.0f;
			idle.currentframe = 0;
			idle.frame.push_back({ 290, 88, 12, 16 });
			idle.frame.push_back({ 306, 80, 16, 24 });
			idle.frame.push_back({ 324, 72, 16, 32 });

			character->animations[ActionState::Idle] = idle;
			transformduration = character->animations[ActionState::Idle].durationtime * character->animations[ActionState::Idle].frame.size();
		}
	}
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->position.y = character->BasePosition - currentframe.height * character->scale;

}

void TransformState::Update(float deltatime) {
	elapsedTime += deltatime;

	if (elapsedTime <= transformduration) {
		Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
		character->position.y = character->BasePosition - currentframe.height * character->scale;
		character->animations[ActionState::Idle].Update(deltatime);
	}
	else {
		switch (transformstate)
		{
		case CharacterTransformState::Super:
			if (character->getCharacterType() == CharacterType::Mario) {
				character->ChangeState(new SuperState(character));
			}
			else if (character->getCharacterType() == CharacterType::Luigi) {
				character->ChangeState(new SuperState(character));
			}
			break;
		default:
			break;
		}
	}
}
