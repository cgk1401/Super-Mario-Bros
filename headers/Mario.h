#pragma once

#include "Character.h"
#include <map>
#include "raylib.h"
#include "NormalState.h"

class Mario : public Character {

public :
	Mario();
	Mario(Vector2 position);
	
	~Mario() override = default;

	CharacterType getCharacterType() override;

};