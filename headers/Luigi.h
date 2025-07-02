#pragma once

#include "Character.h"
#include "NormalState.h"
#include <map>

class Luigi : public Character {

public :
	Luigi();
	Luigi(Vector2 position);

	~Luigi() override = default;

	CharacterType getCharacterType() override;

};
