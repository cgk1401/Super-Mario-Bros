#include "../headers/FireState.h"
#include <raylib.h>

FireState::FireState(Character* character) : CharacterState(character) {
	Singleton<AnimationManager>::getInstance().LoadAnimation("../Assets/Animation/FireState.json", CharacterStateType::FireState);
}

FireState::~FireState() {
	for (auto fireball : fireballs) {
		delete fireball;
	}
	fireballs.clear();
}

void FireState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		character->texture = Singleton<TextureManager>::getInstance().load(TextureType::MARIO);

		character->animations[ActionState::Idle] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::FireState,
			ActionState::Idle
		);

		character->animations[ActionState::Run] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::FireState,
			ActionState::Run
		);

		character->animations[ActionState::Jump] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::FireState,
			ActionState::Jump
		);

		character->animations[ActionState::Sit] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::FireState,
			ActionState::Sit
		);

		character->animations[ActionState::FlagpoleHold] = Singleton<AnimationManager>::getInstance().getAnimation(
			CharacterType::Mario,
			CharacterStateType::FireState,
			ActionState::FlagpoleHold
		);

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
	character->animations[character->currentAction].Update(deltatime);
	// cập nhật Baseposition
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->BasePosition = character->position.y + currentframe.height * character->scale;
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
			//if (IsKeyDown(KEY_P)) {
			//	character->setActionState(ActionState::FlagpoleHold);
			//}
		} 
	}

	character->position.x += character->velocity.x * deltatime;
	character->position.y += character->velocity.y * deltatime;
}

void FireState::HandleInput(float deltatime) {
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
			//if (IsKeyDown(KEY_P)) {
			//	character->setActionState(ActionState::FlagpoleHold);
			//}
			//else {
				// không bấm phím nào thì sẽ đặt trạng thái thành idle
				character->velocity.x = 0.0f;
				character->setActionState(ActionState::Idle);
			//}
		}
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

CharacterStateType FireState::getStateType() {
	return CharacterStateType::FireState;
}

vector<FireBall*> FireState::getFireBall() {
	return fireballs;
}
