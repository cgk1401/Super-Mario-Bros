#include "../headers/StarmanState.h"

StarmanState::StarmanState(Character* character, CharacterStateType previousState) : CharacterState(character) {
	this->previousState = previousState;
}

void StarmanState::SetAnimation(Character* c) {
	if (c->getCharacterType() == CharacterType::Mario) {
		if (previousState == CharacterStateType::NormalState) {
			cout << "2";
			character->texture = TextureManager::get().load(TextureType::MARIOINVINCIBILITY);

			Animation idle;
			idle.currentframe = 0;
			idle.currenttime = 0;
			idle.durationtime = 0.1f;
			const float widthidle = 12;
			const float widthheight = 16;
			for (int i = 0; i < 8; i++) {
				idle.frame.push_back( Rectangle{82, float(225 + 63 * i), widthidle, widthheight});
			}
			character->animations[ActionState::Idle] = idle;

			Animation run;
			run.currentframe = 0;
			run.currenttime = 0;
			run.durationtime = 0.1f;
			run.frame.push_back({ 98, 226, 13, 15 });  // Color 1
			run.frame.push_back({ 117, 225, 11, 16 }); // Color 1
			run.frame.push_back({ 131, 225, 15, 16 }); // Color 1

			run.frame.push_back({ 98, 289, 13, 15 });  // Color 2
			run.frame.push_back({ 117, 288, 11, 16 }); // Color 2
			run.frame.push_back({ 131, 288, 15, 16 }); // Color 2

			run.frame.push_back({ 98, 352, 13, 15 });  // Color 3
			run.frame.push_back({ 117, 351, 11, 16 }); // Color 3
			run.frame.push_back({ 131, 351, 15, 16 }); // Color 3

			run.frame.push_back({ 98, 415, 13, 15 });  // Color 4
			run.frame.push_back({ 117, 414, 11, 16 }); // Color 4
			run.frame.push_back({ 131, 414, 15, 16 }); // Color 4

			run.frame.push_back({ 98, 478, 13, 15 });  // Color 5
			run.frame.push_back({ 117, 477, 11, 16 }); // Color 5
			run.frame.push_back({ 131, 477, 15, 16 }); // Color 5

			run.frame.push_back({ 98, 541, 13, 15 });  // Color 6
			run.frame.push_back({ 117, 540, 11, 16 }); // Color 6
			run.frame.push_back({ 131, 540, 15, 16 }); // Color 6

			run.frame.push_back({ 98, 604, 13, 15 });  // Color 7
			run.frame.push_back({ 117, 603, 11, 16 }); // Color 7
			run.frame.push_back({ 131, 603, 15, 16 }); // Color 7

			run.frame.push_back({ 98, 667, 13, 15 });  // Color 8
			run.frame.push_back({ 117, 666, 11, 16 }); // Color 8
			run.frame.push_back({ 131, 666, 15, 16 }); // Color 8

			character->animations[ActionState::Run] = run;

			Animation jump;
			jump.currentframe = 0;
			jump.currenttime = 0;
			jump.durationtime = 0.1f;
			jump.frame.push_back({ 165, 225, 16, 16 }); // Color 1
			jump.frame.push_back({ 165, 288, 16, 16 }); // Color 2
			jump.frame.push_back({ 165, 351, 16, 16 }); // Color 3
			jump.frame.push_back({ 165, 414, 16, 16 }); // Color 4
			jump.frame.push_back({ 165, 477, 16, 16 }); // Color 5
			jump.frame.push_back({ 165, 540, 16, 16 }); // Color 6
			jump.frame.push_back({ 165, 603, 16, 16 }); // Color 7
			jump.frame.push_back({ 165, 666, 16, 16 }); // Color 8

			character->animations[ActionState::Jump] = jump;

			Animation die;
			die.currentframe = 0;
			die.currenttime = 0;
			die.durationtime = 0.1f;
			die.frame.push_back({ 183, 225, 14, 14 }); // Color 1
			die.frame.push_back({ 183, 288, 14, 14 }); // Color 2
			die.frame.push_back({ 183, 351, 14, 14 }); // Color 3
			die.frame.push_back({ 183, 414, 14, 14 }); // Color 4
			die.frame.push_back({ 183, 477, 14, 14 }); // Color 5
			die.frame.push_back({ 183, 540, 14, 14 }); // Color 6
			die.frame.push_back({ 183, 603, 14, 14 }); // Color 7
			die.frame.push_back({ 183, 666, 14, 14 }); // Color 8
			character->animations[ActionState::Die] = die;

			Animation flagpolehold;
			flagpolehold.currentframe = 0;
			flagpolehold.currenttime = 0;
			flagpolehold.durationtime = 0.1f;
			flagpolehold.frame.push_back({ 201, 225, 12, 16 }); //Color 1
			flagpolehold.frame.push_back({ 218, 226, 12, 15 }); // Color 1

			flagpolehold.frame.push_back({ 201, 288, 12, 16 }); //Color 2
			flagpolehold.frame.push_back({ 218, 229, 12, 15 }); // Color 2

			flagpolehold.frame.push_back({ 201, 351, 12, 16 }); //Color 3
			flagpolehold.frame.push_back({ 218, 352, 12, 15 }); // Color 3

			flagpolehold.frame.push_back({ 201, 414, 12, 16 }); //Color 4
			flagpolehold.frame.push_back({ 218, 415, 12, 15 }); // Color 4

			flagpolehold.frame.push_back({ 201, 477, 12, 16 }); //Color 5
			flagpolehold.frame.push_back({ 218, 478, 12, 15 }); // Color 5

			flagpolehold.frame.push_back({ 201, 540, 12, 16 }); //Color 6
			flagpolehold.frame.push_back({ 218, 541, 12, 15 }); // Color 6

			flagpolehold.frame.push_back({ 201, 603, 12, 16 }); //Color 7
			flagpolehold.frame.push_back({ 218, 604, 12, 15 }); // Color 7

			flagpolehold.frame.push_back({ 201, 666, 12, 16 }); //Color 8
			flagpolehold.frame.push_back({ 218, 667, 12, 15 }); // Color 8

			character->animations[ActionState::FlagpoleHold] = flagpolehold;
		}
		else if (previousState == CharacterStateType::SuperState || previousState == CharacterStateType::FireState) {
		}

	}
	else if (character->getCharacterType() == CharacterType::Luigi) {

	}
	cout << "3";
	Rectangle currentframe = character->animations[character->currentAction].getcurrentframe();
	character->position.y = character->BasePosition - currentframe.height * character->scale;
}

void StarmanState::Update(float deltatime) {
	character->animations[character->currentAction].Update(deltatime);


}

void StarmanState::HandleInput(float deltatime) {

}

CharacterStateType StarmanState::getStateType() {
	return CharacterStateType::StarmanState;
}
