#include "../headers/FireState.h"
#include <raylib.h>

FireState::FireState(Character* character) : CharacterState(character) {}

FireState::~FireState() {
	for (auto fireball : fireballs) {
		delete fireball;
	}
	fireballs.clear();
}

void FireState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIO);

		Animation idle;
		idle.currentframe = 0;
		idle.currenttime = 0;
		idle.durationtime = 0.1f;
		idle.frame.push_back({ 0, 140, 16, 32 });

		character->animations[ActionState::Idle] = idle;

		Animation run;
		run.currentframe = 0;
		run.currenttime = 0;
		run.durationtime = 0.1f;
		run.frame.push_back({ 20, 140, 16, 32 });
		run.frame.push_back({ 38, 140, 16, 32});
		run.frame.push_back({ 56, 140, 16, 32 });

		character->animations[ActionState::Run] = run;

		Animation jump;
		jump.currentframe = 0;
		jump.currenttime = 0;
		jump.durationtime = 0.1f;
		jump.frame.push_back({ 96, 140, 16, 32 });

		character->animations[ActionState::Jump] = jump;

		Animation sit;
		sit.currentframe = 0;
		sit.currenttime = 0;
		sit.durationtime = 0.1f;
		sit.frame.push_back({ 116, 150, 16, 22 });

		character->animations[ActionState::Sit] = sit;

		Animation flagpolehold;
		flagpolehold.currentframe = 0;
		flagpolehold.currenttime = 0;
		flagpolehold.durationtime = 0.1f;
		flagpolehold.frame.push_back({ 136, 139, 16, 32 });
		flagpolehold.frame.push_back({ 154, 139, 16, 32 });

		character->animations[ActionState::FlagpoleHold] = flagpolehold;

		Animation fireball;
		fireball.currentframe = 0;
		fireball.currenttime = 0;
		fireball.durationtime = 0.1f;
		fireball.frame.push_back({ 136, 180, 16, 32 });

		character->animations[ActionState::Fireball] = fireball;
	}

	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->position.y = character->BasePosition - currentframe.height * character->scale;
}

void FireState::Update(float deltatime) {
	HandleInput(deltatime);
	for (auto fireball : fireballs) {
		fireball->Update(deltatime);
	}

	for (auto it = fireballs.begin(); it != fireballs.end();) {
		if (!(*it)->isActive) {
			delete* it;
			it = fireballs.erase(it);
		}
		else {
			++it;
		}
	}


	if (IsKeyPressed(KEY_R)) {
		character->ChangeMiddleState(CharacterStateType::StarmanState);
	}

	if (IsKeyPressed(KEY_Y)) {
		character->ChangeMiddleState(CharacterStateType::NormalState);
	}
}

void FireState::HandleInput(float deltatime) {
	
	if (IsKeyDown(KEY_DOWN)) {
		if (character->isGround) {
			character->velocity.x = 0;
			character->setActionState(ActionState::Sit);

		}
		return;
	}

	
	// if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_DOWN)) {
		if (IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyPressed(KEY_RIGHT_CONTROL)) {
			if (fireballs.size() < maxFireBalls) {
				FireBall* fireball;
				if (character->currentdirection == Direction::Right) {
					fireball = new FireBall({ character->position.x + character->animations[character->currentAction].getcurrentframe().width * character->scale + 20,
					character->position.y + 30 }, character, character->BasePosition);
					fireball->SetVelocity({ fireball->FIREBALL_SPEEDX , 500 });
				}
				else if (character->currentdirection == Direction::Left) {
					fireball = new FireBall({ character->position.x - character->animations[character->currentAction].getcurrentframe().width * character->scale + 20,
					character->position.y + 30 }, character, character->BasePosition);
					fireball->SetVelocity({ -fireball->FIREBALL_SPEEDX , 500 });
				}

				fireballs.push_back(fireball);
			}
		}
		// else if (IsKeyDown(KEY_P)) {
		// 	// trạng thái đang ở trên mặt đất, nhấn KEY_P sẽ đặt trạng thái thành FlagpoleHold
		// 	character->setActionState(ActionState::FlagpoleHold);
		// }
		else if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL) && fireballs.size() != 0) {
			character->setActionState(ActionState::Fireball);
		}
		// else {
		// 	// không bấm phím nào thì sẽ đặt trạng thái thành idle
		// 	character->velocity.x = 0.0f;
		// 	character->setActionState(ActionState::Idle);
		// }
	
	


}

CharacterStateType FireState::getStateType() {
	return CharacterStateType::FireState;
}

vector<FireBall*>& FireState::getFireBall() {
	return fireballs;
}
