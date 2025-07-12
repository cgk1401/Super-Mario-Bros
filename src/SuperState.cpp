#include "../headers/SuperState.h"
#include <raylib.h>

SuperState::SuperState(Character* character) : CharacterState(character){}

void SuperState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = TextureManager::get().load(TextureType::MARIOINVINCIBILITY);
		
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
		run.frame.push_back({ 97, 3, 16, 30 });
		run.frame.push_back({ 115, 2, 14, 31 });
		run.frame.push_back({ 131, 1, 16, 32 });

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
		flagpolehold.frame.push_back({ 201, 3, 14, 30 });
		flagpolehold.frame.push_back({ 218, 3, 14, 27 });

		character->animations[ActionState::FlagpoleHold] = flagpolehold;
		
	}
	else if (c->getCharacterType() == CharacterType::Luigi) {
		character->texture = TextureManager::get().load(TextureType::MARIO);

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
		run.frame.push_back({ 344, 32, 16, 32 });

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.1f;
		jump.frame.push_back({ 384, 32, 16, 32 });

		character->animations[ActionState::Jump] = jump;

		Animation sit;
		sit.currentframe = 0;
		sit.currenttime = 0;
		sit.durationtime = 0.1f;
		sit.frame.push_back({ 404, 42, 16, 22 });

		character->animations[ActionState::Sit] = sit;

		Animation flagpolehold;
		flagpolehold.currentframe = 0;
		flagpolehold.currenttime = 0;
		flagpolehold.durationtime = 0.1f;
		flagpolehold.frame.push_back({ 424, 33, 16, 32 });
		flagpolehold.frame.push_back({ 442, 33, 16, 32 });

		character->animations[ActionState::FlagpoleHold] = flagpolehold;
	}

	// cập nhật position cho SuperState;
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->position.y = character->BasePosition - currentframe.height * character->scale;
}

void SuperState::Update(float deltatime) {
	character->animations[character->currentAction].Update(deltatime);

	HandleInput(deltatime);
	if (!isGround) {
		if (isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME && IsKeyDown(KEY_SPACE)) {
			character->velocity.y += config.GRAVITY * 0.1f * deltatime; // Trọng lực nhẹ hơn khi giữ phím nhảy
		}
		else {
			character->velocity.y += config.GRAVITY * deltatime; // Trọng lực bình thường khi không giữ hoặc hết thời gian tối đa
		}
		if(isJumpingUp) character->setActionState(ActionState::Jump);
	}
	else {
		if (fabs(character->velocity.x) < 0.1f) {
			if (IsKeyDown(KEY_P)) {
				character->setActionState(ActionState::FlagpoleHold);
			 }
			// else {
			// 	character->setActionState(ActionState::Idle);
			// }
		} 
		// else {
		// 	character->setActionState(ActionState::Run);
		// }
	}

	character->position.x += character->velocity.x * deltatime;
	character->position.y += character->velocity.y * deltatime;

	// trạng thái đang rơi xuống
	

	// nhấn phím KEY_I để chuyển trạng thái từ Superstate sang FireState
	if (IsKeyPressed(KEY_I)) {
		character->ChangeMiddleState(CharacterStateType::StarmanState);
	}
}

void SuperState::HandleInput(float deltatime) {
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
	else if (IsKeyDown(KEY_DOWN)) {
		if (isGround) {
			character->setActionState(ActionState::Sit);
			character->velocity.x = 0;
		}

	}

	if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_DOWN)) {
		if (isGround) {
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

	// xử lý nhảy
	// if (IsKeyPressed(KEY_SPACE) && isGround && character->currentAction != ActionState::Sit) {
	// 	character->velocity.y = config.JUMPFORCE;
	// 	isGround = false;
	// 	isJumpingUp = true;
	// 	jumpTimeElapsed = 0.0f;
	// 	character->setActionState(ActionState::Jump);
	// }

	// if (IsKeyDown(KEY_SPACE) && isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME) {
	// 	jumpTimeElapsed += deltatime;
	// }
	// else if (isJumpingUp && !IsKeyDown(KEY_SPACE)) {
	// 	isJumpingUp = false;
	// }

	if (IsKeyDown(KEY_SPACE)) {
	if (isGround) {
		character->velocity.y = config.JUMPFORCE;
		isGround = false;
		isJumpingUp = true;
		jumpTimeElapsed = 0.0f;
	}
	else if (isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME) {
		jumpTimeElapsed += deltatime;
		character->velocity.y = config.JUMPFORCE;  // hoặc scale theo thời gian
	}
	} else {
		isJumpingUp = false;
	}

}

CharacterStateType SuperState::getStateType() {
	return CharacterStateType::SuperState;
}
