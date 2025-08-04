#include "../headers/SuperState.h"
#include <raylib.h>

SuperState::SuperState(Character* character) : CharacterState(character){
	Singleton<AnimationManager>::getInstance().LoadAnimation("../Assets/Animation/SuperState.json", CharacterStateType::SuperState);
}

void SuperState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);

		character->animations[ActionState::Idle] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::SuperState,
			ActionState::Idle
		);

		character->animations[ActionState::Run] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::SuperState,
			ActionState::Run
		);

		character->animations[ActionState::Jump] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::SuperState,
			ActionState::Jump
		);

		character->animations[ActionState::Sit] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::SuperState,
			ActionState::Sit
		);

		character->animations[ActionState::FlagpoleHold] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::SuperState,
			ActionState::FlagpoleHold
		);
	}
	else if (c->getCharacterType() == CharacterType::Luigi) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);

		character->animations[ActionState::Idle] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Luigi,
			CharacterStateType::SuperState,
			ActionState::Idle
		);

		character->animations[ActionState::Run] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Luigi,
			CharacterStateType::SuperState,
			ActionState::Run
		);

		character->animations[ActionState::Jump] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Luigi,
			CharacterStateType::SuperState,
			ActionState::Jump
		);

		character->animations[ActionState::Sit] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Luigi,
			CharacterStateType::SuperState,
			ActionState::Sit
		);

		character->animations[ActionState::FlagpoleHold] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Luigi,
			CharacterStateType::SuperState,
			ActionState::FlagpoleHold
		);
	}

	// cập nhật position cho SuperState;
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->position.y = character->BasePosition - currentframe.height * character->scale;
}

void SuperState::Update(float deltatime) {
	
	HandleInput(deltatime);


}

void SuperState::HandleInput(float deltatime) {
	
	// if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_DOWN)) {
	// 	if (character->isGround) {
	// 		// trạng thái đang ở trên mặt đất, nhấn KEY_P sẽ đặt trạng thái thành FlagpoleHold
	// 		//if (IsKeyDown(KEY_P)) {
	// 			//haracter->setActionState(ActionState::FlagpoleHold);
	// 		//}
	// 		//else {
	// 			// không bấm phím nào thì sẽ đặt trạng thái thành idle
	// 			character->velocity.x = 0.0f;
	// 			character->setActionState(ActionState::Idle);
	// 		//}
	// 	}
	// }

	

}

CharacterStateType SuperState::getStateType() {
	return CharacterStateType::SuperState;
}
