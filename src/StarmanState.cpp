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
		character->texture = TextureManager::get().load(TextureType::MARIOINVINCIBILITY);

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
		character->texture = TextureManager::get().load(TextureType::MARIOINVINCIBILITY);

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

	if (currentTime >= duration) {
		character->setActionState(ActionState::Idle);
		character->ChangeMiddleState(previousState);
	}
}

void StarmanState::HandleInput(float deltatime) {

}

CharacterStateType StarmanState::getStateType() {
	return CharacterStateType::StarmanState;
}
