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
class GameObject;
class Character;

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
	TransforSmallMario,
	TransforSmallLuigi,
};
inline CharacterType selectedCharacter = CharacterType::Mario;

enum class Direction {
	Left,
	Right,
	Top,
	Bottom,
	None,
};

enum class EnemyType {
	None,
	GOOMBA,
	KOOPA,
	REDKOOPA,
	KOOPA_PARATROOPA,
	KOOPA_SHELL,
	REDKOOP_SHELL,
	PIRANT_PLANT,
	FIRE_BAR,
	BOWSER,
};


enum class ItemType {
	NONE,
	COIN,
	MUSHROOM,
	FLOWER,
	STAR,
	FIRE_BAR,
	BOWSER_FIRE_BALL,
	VERTICAL_LIFT,
	HORIZONATAL_LIFT,
};

enum class DeathType
{
	STOMP,
	FALLING,
	SHELL_HIT,
	FIREBALL_HIT,
};

//extern Character* globalcharacter;

class Global {
public:
    static Map* map;
	static Camera2D camera;
	static pair<int,int> level;
	static Character* character;
};

bool operator==(pair<int, int> a, pair<int,int>b);
inline int operator+(int lhs, MapTheme rhs);
float approach(float current, float target, float increase);
//float lerp(float a, float b, float t);

Direction getCollisionDirection(GameObject* a, GameObject* b);
Direction getCollisionDirection(const Rectangle& rectA, const Rectangle& rectB);




struct ButtonLayoutConfig {
    int amount_button;

    float MARGIN_ON;
    float MENU_BUTTON_HEIGHT;

    float BUTTON_MARGIN_X;
    float FIRST_POSITION_Y_BUTTON;
    float BUTTON_SPACING;

    float BUTTON_HEIGHT;
    float BUTTON_WIDTH;

    int FONT_SIZE;
    ButtonLayoutConfig(int amount_button, int fontSize = 30);
};

std::vector <Button*> CreateButtons(const char* buttonLabels[], const ButtonLayoutConfig& other);
#endif 