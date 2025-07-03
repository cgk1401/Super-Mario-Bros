#include "../headers/SuperState.h"
#include "../headers/Character.h"
#include <raylib.h>

SuperState::SuperState(Character* character) : CharacterState(character){}

void SuperState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = LoadTexture("../Assets/Mario/Mario_&_Luigi.png");

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		idle.frame.push_back({ 0, 32, 16, 32 });

		character->animations[ActionState::Idle] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.1f;
		run.frame.push_back({ 20, 32, 16, 32 });
		run.frame.push_back({ 56, 32, 16, 32 });

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.1f;
		jump.frame.push_back({ 96, 32, 16, 32 });

		character->animations[ActionState::Jump] = jump;

		Animation sit;
		sit.currentframe = 0;
		sit.currenttime = 0;
		sit.durationtime = 0.1f;
		sit.frame.push_back({ 116, 42, 16, 22 });

		character->animations[ActionState::Sit] = sit;
	}
	else if (c->getCharacterType() == CharacterType::Luigi) {
		character->texture = LoadTexture("../Assets/Mario/Mario_&_Luigi.png");

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		idle.frame.push_back({ 288, 32, 16, 32 });

		character->animations[ActionState::Idle] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.1f;
		run.frame.push_back({ 308, 32, 16, 32 });
		run.frame.push_back({ 344, 32, 13, 16 });

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.1f;
		jump.frame.push_back({ 384, 32, 16, 16 });

		character->animations[ActionState::Jump] = jump;

		Animation sit;
		sit.currentframe = 0;
		sit.currenttime = 0;
		sit.durationtime = 0.1f;
		sit.frame.push_back({ 404, 40, 16, 24 });

		character->animations[ActionState::Sit] = sit;
	}

}
void SuperState::Update(float deltatime) {

}

void SuperState::HandleInput(float deltatime) {

}
