#include "../Headers/NormalState.h"
#include "../headers/Character.h"
#include <raylib.h>

NormalState::NormalState(Character* character) : CharacterState(character){}

void NormalState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = LoadTexture("../Assets/Mario/Mario_&_Luigi.png");

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		idle.frame.push_back({ 2, 8, 12, 16 });

		character->animations[ActionState::Idle] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.1f;
		run.frame.push_back({ 20, 8, 15, 16 });
		run.frame.push_back({ 58, 8, 13, 17 });

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.1f;
		jump.frame.push_back({ 96, 8, 16, 16 });

		character->animations[ActionState::Jump] = jump;

		Animation die;
		die.currentframe = 0;
		die.currenttime = 0;
		die.durationtime = 0.1f;
		die.frame.push_back({ 117, 8, 14, 14 });

		character->animations[ActionState::Die] = die;
		
	}
	else if (c->getCharacterType() == CharacterType::Luigi) {
		character->texture = LoadTexture("../Assets/Mario/Mario_&_Luigi.png");

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		idle.frame.push_back({ 290, 8, 12, 16 });

		character->animations[ActionState::Idle] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.1f;
		run.frame.push_back({ 308, 8, 15, 16 });
		run.frame.push_back({ 346, 8, 13, 16 });

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.1f;
		jump.frame.push_back({ 384, 8, 16, 16 });

		character->animations[ActionState::Jump] = jump;

		Animation die;
		die.currentframe = 0;
		die.currenttime = 0;
		die.durationtime = 0.1f;
		die.frame.push_back({ 405, 8, 14, 14 });

		character->animations[ActionState::Die] = die;
	}
}

void NormalState::Update(float deltatime) {
	character->animations[character->currentAction].Update(deltatime);

	HandleInput(deltatime);
	if (!isGround) {
		if (isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME && IsKeyDown(KEY_SPACE)) {
			character->velocity.y += config.GRAVITY * 0.1f * deltatime; // Trọng lực nhẹ hơn khi giữ phím nhảy
		}
		else {
			character->velocity.y += config.GRAVITY * deltatime; // Trọng lực bình thường khi không giữ hoặc hết thời gian tối đa
		}
		character->setActionState(ActionState::Jump);
	}

	character->position.x += character->velocity.x * deltatime;
	character->position.y += character->velocity.y * deltatime;

	if (character->position.y >= BasePosition) {
		character->position.y = BasePosition;
		character->velocity.y = 0;
		isGround = true;
		isJumpingUp = false;

		if (fabs(character->velocity.x) < 0.1f) {
			character->setActionState(ActionState::Idle);
		}
		else {
			character->setActionState(ActionState::Run);
		}
	}
}

void NormalState::HandleInput(float deltatime) {
	float targetspeed = IsKeyDown(KEY_LEFT_CONTROL) ? config.MAX_SPEED : config.SPEED;
	float acc = config.ACCELERATION;

	if (IsKeyDown(KEY_RIGHT)) {
		if (character->velocity.x < 0) acc *= 3.0f; // tăng gia tốc khi đổi hướng
		character->velocity.x = approach(character->velocity.x, targetspeed, acc * deltatime);
		character->setActionState(ActionState::Run);
		character->setDirection(Direction::Right);
	}
	else if (IsKeyDown(KEY_LEFT)) {
		if (character->velocity.x > 0) acc *= 3.0f;
		character->velocity.x = approach(character->velocity.x, -targetspeed, acc * deltatime);
		character->setActionState(ActionState::Run);
		character->setDirection(Direction::Left);
	}

	if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
		if (isGround) {
			character->velocity.x = 0.0f;
			character->setActionState(ActionState::Idle);
		}
	}

	// xử lý nhảy
	if (IsKeyPressed(KEY_SPACE) && isGround) {
		character->velocity.y = config.JUMPFORCE;
		isGround = false;
		isJumpingUp = true;
		jumpTimeElapsed = 0.0f;
		character->setActionState(ActionState::Jump);
	}

	if (IsKeyDown(KEY_SPACE) && isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME) {
		jumpTimeElapsed += deltatime;
	}
	else if (isJumpingUp && !IsKeyDown(KEY_SPACE)) {
		isJumpingUp = false;
	}
}

