#include "../headers/StarmanState.h"

StarmanState::StarmanState(Character* character, CharacterStateType previousState) : CharacterState(character) {
	this->previousState = previousState;
}

void StarmanState::SetAnimation(Character* c) {
	float posX;
	float posY;
	float width;
	float height;
	if (previousState == CharacterStateType::NormalState) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		posX = 82;
		posY = 225;
		width = 12;
		height = 16;

		for (int Color = 0; Color < 8; Color++) {
			idle.frame.push_back( Rectangle{posX, float(posY + 63 * Color), width, height});
		}

		character->animations[ActionState::Idle] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.1f;

		for (int Color = 0; Color < 8; Color++) {
			for (int i = 0; i < 3; i++) {
				if (i == 0) {
					posX = 98;
					posY = 226;
					width = 13;
					height = 15;
				}
				else if (i == 1) {
					posX = 117;
					posY = 225;
					width = 11;
					height = 16;
				}
				else if (i == 2) {
					posX = 131;
					posY = 225;
					width = 15;
					height = 16;
				}
				run.frame.push_back({ posX, float(posY + Color * 63), width, height});
			}
		}

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.1f;
		posX = 165;
		posY = 225;
		width = 16;
		height = 16;

		for (int Color = 0; Color < 8; Color++) {
			jump.frame.push_back({ posX, float(posY + 63 * Color), width, height });
		}

		character->animations[ActionState::Jump] = jump;

		Animation die;
		die.currentframe = 0;
		die.currenttime = 0;
		die.durationtime = 0.1f;
		posX = 183;
		posY = 225;
		width = 14;
		height = 14;

		for (int Color = 0; Color < 8; Color++) {
			die.frame.push_back(Rectangle{ posX, float(posY + Color * 63), width, height });
		}

		character->animations[ActionState::Die] = die;

		Animation flagpolehold;
		flagpolehold.currentframe = 0;
		flagpolehold.currenttime = 0;
		flagpolehold.durationtime = 0.1f;
		width = 12;

		for (int Color = 0; Color < 8; Color++) {
			for (int i = 0; i < 2; i++) {
				if (i == 0) {
					posX = 201;
					posY = 225;
					height = 16;
				}
				else if (i == 1) {
					posX = 218;
					posY = 226;
					height = 15;
				}
				flagpolehold.frame.push_back(Rectangle{ posX, float(posY + Color * 63), width, height });
			}
		}

		character->animations[ActionState::FlagpoleHold] = flagpolehold;
	}

	else if (previousState == CharacterStateType::SuperState || previousState == CharacterStateType::FireState) {
		// Frame Mario lớn hơn
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIOINVINCIBILITY);

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		posX = 80;
		posY = 192;
		width = 16;
		height = 32;

		for (int Color = 0; Color < 8; Color++) {
			idle.frame.push_back(Rectangle{ posX, float(posY + 63 * Color), width, height });
		}

		character->animations[ActionState::Idle] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.1f;

		for (int Color = 0; Color < 8; Color++) {
			for (int i = 0; i < 3; i++) {
				if (i == 0) {
					posX = 97;
					posY = 194;
					width = 16;
					height = 30;
				}
				else if (i == 1) {
					posX = 115;
					posY = 193;
					width = 14;
					height = 31;
				}
				else if (i == 2) {
					posX = 131;
					posY = 192;
					width = 16;
					height = 32;
				}
				run.frame.push_back({ posX, float(posY + Color * 63), width, height });
			}
		}
			
		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.1f;
		posX = 165;
		posY = 192;
		width = 16;
		height = 32;

		for (int Color = 0; Color < 8; Color++) {
			jump.frame.push_back({ posX, float(posY + 63 * Color), width, height });
		}

		character->animations[ActionState::Jump] = jump;
			 
		Animation sit;
		sit.currentframe = 0;
		sit.currenttime = 0;
		sit.durationtime = 0.1f;
		posX = 182;
		posY = 202;
		width = 16;
		height = 22;

		for (int Color = 0; Color < 8; Color++) {
			sit.frame.push_back(Rectangle{ posX, float(posY + Color * 63), width, height });
		}

		character->animations[ActionState::Sit] = sit;

		Animation flagpolehold;
		flagpolehold.currentframe = 0;
		flagpolehold.currenttime = 0;
		flagpolehold.durationtime = 0.1f;
		width = 14;

		for (int Color = 0; Color < 8; Color++) {
			for (int i = 0; i < 2; i++) {
				if (i == 0) {
					posX = 201;
					posY = 194;
					height = 30;
				}
				else if (i == 1) {
					posX = 218;
					posY = 194;
					height = 27;
				}
				flagpolehold.frame.push_back(Rectangle{ posX, float(posY + Color * 63), width, height });
			}
		}

		character->animations[ActionState::FlagpoleHold] = flagpolehold;
	}

	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->position.y = character->BasePosition - currentframe.height * character->scale;
}

void StarmanState::Update(float deltatime) {
	currentTime += deltatime;
	character->animations[character->currentAction].Update(deltatime);

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
		if (isJumpingUp) character->setActionState(ActionState::Jump);
		//character->setActionState(ActionState::Jump);
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

	if (currentTime >= duration) {
		character->setActionState(ActionState::Idle);
		character->ChangeMiddleState(previousState);
	}
}

void StarmanState::HandleInput(float deltatime) {
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
	 //if (IsKeyPressed(KEY_SPACE) && isGround && character->currentAction != ActionState::Sit) {
	 //	character->velocity.y = config.JUMPFORCE;
	 //	isGround = false;
	 //	isJumpingUp = true;
	 //	jumpTimeElapsed = 0.0f;
	 //	character->setActionState(ActionState::Jump);
	 //}

	 //if (IsKeyDown(KEY_SPACE) && isJumpingUp && jumpTimeElapsed < config.MAXJUMPTIME) {
	 //	jumpTimeElapsed += deltatime;
	 //}
	 //else if (isJumpingUp && !IsKeyDown(KEY_SPACE)) {
	 //	isJumpingUp = false;
	 //}

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
	}
	else {
		isJumpingUp = false;
	}
}

CharacterStateType StarmanState::getStateType() {
	return CharacterStateType::StarmanState;
}
