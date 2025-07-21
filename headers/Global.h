#ifndef GLOBAL_H
#define GLOBAL_H
#include <raylib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include "Singleton.h"
#include "../headers/Button.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Game.h"
#include "nlohmann/json.hpp"

//using json = nlohmann::json;

using namespace std;
const int screenWidth = 1200; //1024
const int screenHeight = 800; //768
Texture2D resizedImage(const char* imagePath, float width, float height);
class Map;

enum class CharacterStateType {
	NormalState,
	SuperState,
	FireState,
	StarmanState,
	TransformState,
};

enum class ActionState {
	Idle,
	Run,
	Jump,
	Sit,
	Die,
	FlagpoleHold,
	Fireball,
};

enum class CharacterType {
	Mario,
	Luigi,
};
inline CharacterType selectedCharacter = CharacterType::Mario;

enum class Direction {
	Left,
	Right
};

enum class EnemyType {
	GOOMBA,
	KOOPA,
	PIRANT_PLANT
};

class Global {
public:
    static Map* map;
	static Camera2D camera;
};


#endif 