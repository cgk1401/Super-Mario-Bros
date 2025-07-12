#include "../Headers/NormalState.h"
#include <raylib.h>

NormalState::NormalState(Character* character) : CharacterState(character){}

void NormalState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = TextureManager::get().load(TextureType::MARIO);

		const float texW = 16;
		const float texH = 16;

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		idle.frame.push_back({ 0, 8, texW, texH });

		character->animations[ActionState::Idle] = idle;

		Animation run;
		for (int i = 0; i < 3; i++) {
			run.frame.push_back(Rectangle{ (float)(20 + i * 18), 8, (float)texW, (float)texH });
		}
		run.currentframe = 0;
		run.durationtime = 0.07f;
		run.currenttime = 0;

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.frame.push_back(Rectangle{ 96, 8, (float)texW, (float)texH});
		jump.currentframe = 0;
		jump.durationtime = 0.08;
		jump.currenttime = 0;

		character->animations[ActionState::Jump] = jump;

		Animation die;
		die.currentframe = 0;
		die.currenttime = 0;
		die.durationtime = 0.1f;
		die.frame.push_back({ 116, 8, texW, texH });

		character->animations[ActionState::Die] = die;

		Animation flagpolehold;
		flagpolehold.currentframe = 0;
		flagpolehold.currenttime = 0;
		flagpolehold.durationtime = 0.1f;
		flagpolehold.frame.push_back({ 136, 8, texW, texH });
		flagpolehold.frame.push_back({ 154, 8, texW, texH });

		character->animations[ActionState::FlagpoleHold] = flagpolehold;
		
	}
	else if (c->getCharacterType() == CharacterType::Luigi) {
		character->texture = TextureManager::get().load(TextureType::MARIO);

		const float texW = 16;
		const float texH = 16;

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		idle.frame.push_back({ 288, 8, texW, texH });

		character->animations[ActionState::Idle] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.1f;
		run.frame.push_back({308, 8, texW, texH});
		run.frame.push_back({326, 8, texW, texH});
		run.frame.push_back({344, 8, texW,texH});

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
		die.frame.push_back({ 404, 8, texW, texH });

		character->animations[ActionState::Die] = die;

		Animation flagpolehold;
		flagpolehold.currentframe = 0;
		flagpolehold.currenttime = 0;
		flagpolehold.durationtime = 0.1f;
		flagpolehold.frame.push_back({ 424, 8, texW, texH });
		flagpolehold.frame.push_back({ 442, 8, texW, texH });

		character->animations[ActionState::FlagpoleHold] = flagpolehold;
	}
	// cập nhật Baseposition
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->BasePosition += currentframe.height * character->scale;
}

void NormalState::Update(float deltatime) {
	character->animations[character->currentAction].Update(deltatime);
	// cập nhật Baseposition
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->BasePosition = character->position.y +  currentframe.height * character->scale;

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
		character->velocity.y = 0; 
		isJumpingUp = false;
		if (fabs(character->velocity.x) < 0.1f) {
			if (IsKeyDown(KEY_P)) {
				character->setActionState(ActionState::FlagpoleHold);
			} 
			 //else {
			 //	character->setActionState(ActionState::Idle);
			 //}
		} 
		 //else {
		 //	character->setActionState(ActionState::Run);
		 //}
	}
	character->position.x += character->velocity.x * deltatime;
	character->position.y += character->velocity.y * deltatime;

	
	// Nhấn phím KEY_L chuyển trạng thái từ NormalState thành SuperState
	if (IsKeyPressed(KEY_L)) {
		character->ChangeMiddleState(CharacterStateType::StarmanState);
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
	 /*if (IsKeyPressed(KEY_SPACE) && isGround) {
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
	 }*/

	if (IsKeyDown(KEY_SPACE)) {
	if (isGround) {
		SoundManager::get()->play(SoundType::JUMP);
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

CharacterStateType NormalState::getStateType() {
	return CharacterStateType::NormalState;
}

