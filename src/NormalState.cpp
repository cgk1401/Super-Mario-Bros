#include "../Headers/NormalState.h"
#include "../headers/Character.h"
#include <raylib.h>

NormalState::NormalState(Character* character) : CharacterState(character){

}

void NormalState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = LoadTexture("../Assets/Mario/Mario_&_Luigi.png");

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.3f;
		idle.frame.push_back({ 2,8, 12, 16 });

		character->animations[ActionState::IDLE] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.3f;
		run.frame.push_back({ 20, 8, 15, 16 });
		run.frame.push_back({ 58, 8, 13, 17 });

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.3f;
		jump.frame.push_back({ 96, 8, 16, 16 });

		character->animations[ActionState::Jump] = jump;

		Animation die;
		die.currentframe = 0;
		die.currenttime = 0;
		die.durationtime = 0.3f;
		die.frame.push_back({ 117, 8, 14, 14 });

		character->animations[ActionState::DIE] = die;
		
	}
	else if (c->getCharacterType() == CharacterType::Luigi) {
		character->texture = LoadTexture("../Assets/Mario/Mario_&_Luigi.png");

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.3f;
		idle.frame.push_back({ 290,8, 12, 16 });

		character->animations[ActionState::IDLE] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.3f;
		run.frame.push_back({ 308, 8, 15, 16 });
		run.frame.push_back({ 346, 8, 13, 16 });

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.3f;
		jump.frame.push_back({ 384, 8, 16, 16 });

		character->animations[ActionState::Jump] = jump;

		Animation die;
		die.currentframe = 0;
		die.currenttime = 0;
		die.durationtime = 0.3f;
		die.frame.push_back({ 405, 8, 14, 14 });

		character->animations[ActionState::DIE] = die;
	}
}

void NormalState::Update(float deltatime) {
	character->animations[character->currentAction].Update(deltatime);
}
