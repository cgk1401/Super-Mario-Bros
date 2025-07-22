#pragma once

#include "Global.h"
#include "Animation.h"
#include <map>
using namespace std;

template <typename T>
class Singleton;

class AnimationManager {
	template <typename T>
	friend class Singleton;

private :
	map <CharacterType, map <CharacterStateType, map <ActionState, Animation>>> animations;

	AnimationManager() {};
	~AnimationManager() {};
public:
	void LoadAnimation(const string& filename, CharacterStateType statetype);
	Animation getAnimation(CharacterType charactertype, CharacterStateType statetype, ActionState actiontype);


};