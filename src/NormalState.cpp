#include "../Headers/NormalState.h"
#include <raylib.h>

NormalState::NormalState(Character* character) : CharacterState(character){
	character->velocity = { 0, 0 };
}

void NormalState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);

		const float texW = 16;
		const float texH = 16;

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		idle.frame.push_back({ 80, 34, texW, texH });

		character->animations[ActionState::Idle] = idle;

		Animation run;
		for (int i = 0; i < 3; i++) {
			run.frame.push_back(Rectangle{ (float)(80 + i * 17), 34, (float)texW, (float)texH });
		}
		run.currentframe = 0;
		run.durationtime = 0.07f;
		run.currenttime = 0;

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.frame.push_back(Rectangle{ 165, 34, (float)texW, (float)texH});
		jump.currentframe = 0;
		jump.durationtime = 0.08f;
		jump.currenttime = 0;

		character->animations[ActionState::Jump] = jump;

		Animation die;
		die.currentframe = 0;
		die.currenttime = 0;
		die.durationtime = 0.1f;
		die.frame.push_back({ 182, 34, texW, texH });

		character->animations[ActionState::Die] = die;

		Animation flagpolehold;
		flagpolehold.currentframe = 0;
		flagpolehold.currenttime = 0;
		flagpolehold.durationtime = 0.1f;
		for (int i = 0; i < 2; i++) {
			flagpolehold.frame.push_back(Rectangle{ float(199 + i * 17), 334, texW, texH });
		}

		character->animations[ActionState::FlagpoleHold] = flagpolehold;
		
	}
	else if (c->getCharacterType() == CharacterType::Luigi) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIO);

		const float texW = 16;
		const float texH = 16;

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		idle.frame.push_back({ 80, 99, texW, texH });

		character->animations[ActionState::Idle] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.1f;
		for (int i = 0; i < 3; i++) {
			run.frame.push_back(Rectangle{float(80 * 17 + 1), 99, texW, texH});
		}

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.1f;
		jump.frame.push_back({ 165, 99, texW, texH });

		character->animations[ActionState::Jump] = jump;

		Animation die;
		die.currentframe = 0;
		die.currenttime = 0;
		die.durationtime = 0.1f;
		die.frame.push_back({ 182, 99, texW, texH });

		character->animations[ActionState::Die] = die;

		Animation flagpolehold;
		flagpolehold.currentframe = 0;
		flagpolehold.currenttime = 0;
		flagpolehold.durationtime = 0.1f;
		for (int i = 0; i < 2; i++) {
			flagpolehold.frame.push_back(Rectangle{ float(199 + i * 17), 99, texW, texH });
		}

		character->animations[ActionState::FlagpoleHold] = flagpolehold;
	}
	// cập nhật Baseposition
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->BasePosition += currentframe.height * character->scale;
}

void NormalState::Update(float deltatime) {
	

	if (IsKeyPressed(KEY_Q)) {
		character->ChangeMiddleState(CharacterStateType::SuperState);
	}
	
}

void NormalState::HandleInput(float deltatime) {
	

}

CharacterStateType NormalState::getStateType() {
	return CharacterStateType::NormalState;
}

