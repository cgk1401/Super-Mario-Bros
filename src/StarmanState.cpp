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
		posX = 80;
		posY = 225;
		width = 16;
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
					posX = 97;
					posY = 225;
					width = 16;
					height = 16;
				}
				else if (i == 1) {
					posX = 114;
					posY = 225;
					width = 16;
					height = 16;
				}
				else if (i == 2) {
					posX = 131;
					posY = 225;
					width = 16;
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
		width = 16;
		height = 16;

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
					height = 16;
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
					posY = 192;
					width = 16;
					height = 32;
				}
				else if (i == 1) {
					posX = 115;
					posY = 192;
					width = 16;
					height = 32;
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
	
	HandleInput(deltatime);
	
	// trạng thái đang rơi xuống

	if (currentTime >= duration) {
		//character->setActionState(ActionState::Idle);
		cout << "BEGIN CHANGING\n";
		character->ChangeMiddleState(previousState);
		
	}
	cout << 1;
}

void StarmanState::HandleInput(float deltatime) {

	if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_DOWN)) {
		if (character->isGround) {
			// trạng thái đang ở trên mặt đất, nhấn KEY_P sẽ đặt trạng thái thành FlagpoleHold
			if (IsKeyDown(KEY_P)) {
				character->setActionState(ActionState::FlagpoleHold);
			}
			else {
				// không bấm phím nào thì sẽ đặt trạng thái thành idle
				
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

	
}

CharacterStateType StarmanState::getStateType() {
	return CharacterStateType::StarmanState;
}
