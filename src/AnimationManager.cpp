#include "../headers/AnimationManager.h"

void AnimationManager::LoadAnimation(const string& filename, CharacterStateType statetype) {
	ifstream input(filename);

	nlohmann::json json;
	input >> json;

	for (auto& chartype : json.items()) {
		CharacterType type;
		if (chartype.key() == "Mario") type = CharacterType::Mario;
		else if (chartype.key() == "Luigi") type = CharacterType::Luigi;
		else if (chartype.key() == "SmallCharacter") type = CharacterType::SmallCharacter;
		else if (chartype.key() == "BigCharacter") type = CharacterType::BigCharacter;

		for (auto& action : chartype.value().items()) {
			ActionState actionType;
			if (action.key() == "Idle") actionType = ActionState::Idle;
			else if (action.key() == "Run") actionType = ActionState::Run;
			else if (action.key() == "Jump") actionType = ActionState::Jump;
			else if (action.key() == "Die") actionType = ActionState::Die;
			else if (action.key() == "Sit") actionType = ActionState::Sit;
			else if (action.key() == "FlagpoleHold") actionType = ActionState::FlagpoleHold;

			Animation anim;
			anim.currentframe = 0;
			anim.currenttime = 0;
			anim.durationtime = action.value()["duration"];
			for (auto& frame : action.value()["frames"]) {
				anim.frame.push_back({ frame["x"], frame["y"], frame["width"], frame["height"] });
			}
			animations[type][statetype][actionType] = anim;;
		}
	}
	input.close();
}

Animation AnimationManager::getAnimation(CharacterType charactertype, CharacterStateType statetype, ActionState actiontype) {
	return animations[charactertype][statetype][actiontype];
}
