#include "../headers/FireState.h"
#include "../headers/Character.h"
#include <raylib.h>

FireState::FireState(Character* character) : CharacterState(character) {}

void FireState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = LoadTexture("../Assets/Mario/Mario_&_Luigi.png");

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		idle.frame.push_back({ 0, 140, 16, 32 });

		character->animations[ActionState::Idle] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.1f;
		run.frame.push_back({ 20, 142, 16, 30 });
		run.frame.push_back({ 56, 140, 16, 32 });

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.1f;
		jump.frame.push_back({ 96, 140, 16, 32 });

		character->animations[ActionState::Jump] = jump;

		Animation sit;
		sit.currentframe = 0;
		sit.currenttime = 0;
		sit.durationtime = 0.1f;
		sit.frame.push_back({ 116, 150, 16, 22 });

		character->animations[ActionState::Sit] = sit;

		Animation flagpolehold;
		flagpolehold.currentframe = 0;
		flagpolehold.currenttime = 0;
		flagpolehold.durationtime = 0.1f;
		flagpolehold.frame.push_back({ 138, 141, 14, 29 });
		flagpolehold.frame.push_back({ 156, 141, 14, 27 });

		character->animations[ActionState::FlagpoleHold] = flagpolehold;
	}


	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->position.y = character->BasePosition - currentframe.height * character->scale;
}

void FireState::Update(float deltatime) {

}

void FireState::HandleInput(float deltatime) {

}

