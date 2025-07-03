#pragma once

class Character;

class CharacterState {
protected :
	Character* character;

public :
	CharacterState(Character* character);
	virtual ~CharacterState() = default;

	virtual void SetAnimation(Character* c) = 0;
	virtual void Update(float deltatime) = 0;
	virtual void HandleInput(float deltatime) = 0;
	float approach(float current, float target, float increase);

	Character* getCharacter() { return this->character; }
};