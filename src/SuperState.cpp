#include "../headers/SuperState.h"
#include <raylib.h>

SuperState::SuperState(Character* character) : CharacterState(character){}

void SuperState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);
		
		const float texW = 16;
		const float texH = 32;

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		idle.frame.push_back({ 80, 1, 16, 32 });

		character->animations[ActionState::Idle] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.1f;
		for (int i = 0; i < 3; i++) {
			run.frame.push_back(Rectangle{ float(97 + i * 17), 1, texW, texH });
		}

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.1f;
		jump.frame.push_back({ 165, 1, 16, 32 });

		character->animations[ActionState::Jump] = jump;

		Animation sit;
		sit.currentframe = 0;
		sit.currenttime = 0;
		sit.durationtime = 0.1f;
		sit.frame.push_back({ 182, 11, 16, 22 });

		character->animations[ActionState::Sit] = sit; 

		Animation flagpolehold;
		flagpolehold.currentframe = 0;
		flagpolehold.currenttime = 0;
		flagpolehold.durationtime = 0.1f;
		for (int i = 0; i < 2; i++) {
			flagpolehold.frame.push_back(Rectangle{ float(199 + i * 17), 1, 16, 32 });
		}

		character->animations[ActionState::FlagpoleHold] = flagpolehold;
		
	}
	else if (c->getCharacterType() == CharacterType::Luigi) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);

		const float texW = 16;
		const float texH = 32;

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		idle.frame.push_back({ 80, 66, 16, 32 });

		character->animations[ActionState::Idle] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.1f;
		for (int i = 0; i < 3; i++) {
			run.frame.push_back(Rectangle{ float(97 + i * 17), 66, texW, texH });
		}

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.1f;
		jump.frame.push_back({ 165, 66, texW, texH });

		character->animations[ActionState::Jump] = jump;

		Animation sit;
		sit.currentframe = 0;
		sit.currenttime = 0;
		sit.durationtime = 0.1f;
		sit.frame.push_back({ 182, 76, 16, 22 });

		character->animations[ActionState::Sit] = sit;

		Animation flagpolehold;
		flagpolehold.currentframe = 0;
		flagpolehold.currenttime = 0;
		flagpolehold.durationtime = 0.1f;
		for (int i = 0; i < 2; i++) {
			flagpolehold.frame.push_back(Rectangle{ float(199 + i * 17), 66, 16, 32 });
		}

		character->animations[ActionState::FlagpoleHold] = flagpolehold;
	}

	// cập nhật position cho SuperState;
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->position.y = character->BasePosition - currentframe.height * character->scale;
}

void SuperState::Update(float deltatime) {
	
	HandleInput(deltatime);


}

void SuperState::HandleInput(float deltatime) {
	
	if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_DOWN)) {
		if (character->isGround) {
			// trạng thái đang ở trên mặt đất, nhấn KEY_P sẽ đặt trạng thái thành FlagpoleHold
			if (IsKeyDown(KEY_P)) {
				character->setActionState(ActionState::FlagpoleHold);
			}
			else {
				// không bấm phím nào thì sẽ đặt trạng thái thành idle
				character->velocity.x = 0.0f;
				character->setActionState(ActionState::Idle);
			}
		}
	}

	

}

CharacterStateType SuperState::getStateType() {
	return CharacterStateType::SuperState;
}
