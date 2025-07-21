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
	character->animations[character->currentAction].Update(deltatime);
	// cập nhật Baseposition
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->BasePosition = character->position.y + currentframe.height * character->scale;
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


}

void SuperState::HandleInput(float deltatime) {
	float targetspeed = IsKeyDown(KEY_LEFT_CONTROL) ? config.MAX_SPEED : config.SPEED;
	float acc = config.ACCELERATION;

	if (IsKeyDown(KEY_DOWN)) {
		if (isGround) {
			character->velocity.x = 0;
			character->setActionState(ActionState::Sit);
			 
		}
		return;
	}

	if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)) {
		if (character->velocity.x < 0) acc *= 3.0f; // tăng gia tốc khi đổi hướng
		character->velocity.x = approach(character->velocity.x, targetspeed, acc * deltatime);
		character->setActionState(ActionState::Run);
		character->setDirection(Direction::Right);
	}
	else if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
		if (character->velocity.x > 0) acc *= 3.0f;
		character->velocity.x = approach(character->velocity.x, -targetspeed, acc * deltatime);
		character->setActionState(ActionState::Run);
		character->setDirection(Direction::Left);
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
		Singleton<SoundManager>::getInstance().play(SoundType::JUMP);
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
