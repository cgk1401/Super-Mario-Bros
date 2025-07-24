#pragma once

#include "Character.h"
#include <map>
#include "raylib.h"
#include "NormalState.h"
#include "Global.h"

class Luigi : public Character {

public :
	Luigi();
	Luigi(Vector2 position);

	~Luigi() override = default;

	CharacterType getCharacterType() override;

};
