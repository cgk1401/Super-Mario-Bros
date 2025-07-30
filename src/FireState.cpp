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
				Singleton<SoundManager>::getInstance().play(SoundType::FIREBALL);
			}
		}
		// else if (IsKeyDown(KEY_P)) {
		// 	// trạng thái đang ở trên mặt đất, nhấn KEY_P sẽ đặt trạng thái thành FlagpoleHold
		// 	character->setActionState(ActionState::FlagpoleHold);
		// }
		if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL) && fireballs.size() != 0) {
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
