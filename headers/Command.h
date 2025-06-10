#pragma once

#include "Character.h"

class Command {
public :
	virtual void Excute(Character* character) = 0;
	virtual ~Command() = default;
};

class MoveLeft : public Command {
	void Excute(Character* character) {
		character->MoveLeft();
	}
};

class MoveRight : public Command {
	void Excute(Character* character) {
		character->MoveRight();
	}
};

