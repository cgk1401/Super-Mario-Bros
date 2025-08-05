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
const int screenWidth = 1320; //1200 
const int screenHeight = 900; //800
Texture2D resizedImage(const char* imagePath, float width, float height);
class Map;
class Enemy;

constexpr Color DARK_BLUE = { 22, 72, 159, 255 };


enum class MapTheme {
    OVERWORLD   = 0,
    UNDERGROUND = 1,
    CASTLE      = 2,
    UNDERWATER  = 3,
};

enum class LayerType{
    BACKGROUND,
    PLATFORM,
    ENEMY,
    ITEM,
    FOREGROUND,
};

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
	SmallCharacter,
	BigCharacter,
};
inline CharacterType selectedCharacter = CharacterType::Mario;

enum class Direction {
	Left,
	Right
};

enum class EnemyType {
	None,
	GOOMBA,
	KOOPA,
	KOOPA_SHELL,
	PIRANT_PLANT,
	FIRE_BAR,
};


enum class ItemType {
	NONE = 0,
	COIN = 1,
	MUSHROOM = 2,
	FLOWER = 3,
	STAR = 4,
	FIRE_BAR = 5,
};

enum class DeathType
{
	STOMP,
	FALLING,
	SHELL_HIT,
};
class Global {
public:
    static Map* map;
	static Camera2D camera;
	static pair<int,int> level;
};

bool operator==(pair<int, int> a, pair<int,int>b);
inline int operator+(int lhs, MapTheme rhs);
float approach(float current, float target, float increase);
//float lerp(float a, float b, float t);

#endif 