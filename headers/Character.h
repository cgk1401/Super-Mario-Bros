#pragma once

#include "Animation.h"
#include <map>
#include "CharacterState.h"
#include <iostream>

using namespace std;

class CharacterState;
class NormalState;

class Map;

enum class ActionState {
	IDLE,
	Run,
	Jump,
	Fall,
	DIE,
};

enum class Direction {
	Left,
	Right
};

enum class CharacterType {
	Mario,
	Luigi,
};

class Character {
	friend class CharacterState;
	friend class NormalState;

protected:


public:
	virtual ~Character();

};