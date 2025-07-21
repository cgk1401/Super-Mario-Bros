#include "../Headers/NormalState.h"
#include <raylib.h>

NormalState::NormalState(Character* character) : CharacterState(character){
	character->velocity = { 0, 0 };
	Singleton<AnimationManager>::getInstance().LoadAnimation("../Assets/NormalState.json", CharacterStateType::NormalState);
}

void NormalState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);
		
		const float texW = 16;
		const float texH = 16;

		character->animations[ActionState::Idle] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::NormalState,
			ActionState::Idle
		);

		character->animations[ActionState::Run] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::NormalState,
			ActionState::Run
		);

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
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);

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
			run.frame.push_back(Rectangle{float(80 + 17 * i), 99, texW, texH});
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
	character->animations[character->currentAction].Update(deltatime);
	// cập nhật Baseposition
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->BasePosition = character->position.y +  currentframe.height * character->scale;

	HandleInput(deltatime);
	if (!isGround) {
		if (isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME && IsKeyDown(KEY_SPACE)) {
			character->velocity.y += config.GRAVITY * 0.1f * deltatime; // Trọng lực nhẹ hơn khi giữ phím nhảy
			//cout << "not on ground 1\n";
		}
		else {
			character->velocity.y += config.GRAVITY * deltatime; // Trọng lực bình thường khi không giữ hoặc hết thời gian tối đa
			//cout << "not on ground 2\n";
		}
		if(isJumpingUp) character->setActionState(ActionState::Jump);
	}
	else {
		//cout << "on ground\n";
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
	//cout << "vY: " << character->velocity.y << ", isGround: " << isGround << endl;

	if (IsKeyPressed(KEY_Q)) {
		character->ChangeMiddleState(CharacterStateType::SuperState);
	}
	
}

void NormalState::HandleInput(float deltatime) {
	float targetspeed = IsKeyDown(KEY_LEFT_CONTROL) ? config.MAX_SPEED : config.SPEED;
	float acc = config.ACCELERATION;

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

	if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
		if (isGround) {
			character->velocity.x = 0.0f;
			character->setActionState(ActionState::Idle);
		}
	}
	
	 //xử lý nhảy
	 //if (IsKeyPressed(KEY_SPACE) && isGround) {
	 //	character->velocity.y = config.JUMPFORCE;
	 //	isGround = false;
	 //	isJumpingUp = true;
	 //	jumpTimeElapsed = 0.0f;
	 //	character->setActionState(ActionState::Jump);
	 //}

	 //if (IsKeyDown(KEY_SPACE) && isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME) {
		// //Singleton<SoundManager>::getInstance().play(SoundType::JUMP);
	 //	jumpTimeElapsed += deltatime;
	 //}
	 //else if (isJumpingUp && !IsKeyDown(KEY_SPACE)) {
	 //	isJumpingUp = false;
	 //}

	if (IsKeyDown(KEY_SPACE)) {
		if (isGround) {
			Singleton<SoundManager>::getInstance().play(SoundType::JUMP_SMALL);
			character->velocity.y = config.JUMPFORCE;
			isGround = false;
			isJumpingUp = true; 
			jumpTimeElapsed = 0.0f;
		}
		else if (isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME && !isGround) {
			jumpTimeElapsed += deltatime;
			character->velocity.y = config.JUMPFORCE;  // hoặc scale theo thời gian
			//cout << "is jumpin\n";
		}
	} else {
		isJumpingUp = false;
	}

}

CharacterStateType NormalState::getStateType() {
	return CharacterStateType::NormalState;
}

