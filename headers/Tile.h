#pragma once
#include "raylib.h"
#include "TileBehavior.h"
#include "../headers/Global.h"
enum TileType {
	EMPTY = 0,
	GROUND,
	BRICK,
	HORIZONTAL_PIPE,
	VERTICAL_PIPE,
	COIN,
	COINS_BLOCK,			//A block of multiple coins
	QUESTION_BLOCK,			// consisting of coin, power-up items such as flower, star,. depending on game, level or mario's super form
	USED_QUESTION_BLOCK,
	DECORATION_BLOCK,		// background tile, not interactable
	ITEM,					// item tile, can be mushroom, flower, star, coin, etc.
	LAVA_FLOOR,				// lava tile, can be used for traps
	FINISHING_POLE,			// finishing pole tile, used in some levels to mark the end. trigger some events when mario touches it
	ENEMY,
	STAR_BRICK,
	FIREBAR_BLOCK,
	BLACK_BLOCK,
	VERTICAL_LIFT,
	HORIZONTAL_LIFT,
	//list ra hết mấy loại tile nha...
};

//Info của từng tile
class Tile {
public:
	int id;								// id trong tileset
	Rectangle srcRect;					// vi tri trong tileset
	TileType type;						// loai tile: brick, pipe, empty,...
	TileBehavior* behavior;				// behavior of each tile
	MapTheme theme;
	LayerType layerType;

	Tile(int _id = 0, Rectangle _sourceRect = { 0 }, TileType _type = EMPTY, TileBehavior* _behavior = nullptr, MapTheme _theme = MapTheme::OVERWORLD, LayerType _layerType = LayerType::BACKGROUND)
		: id(_id), srcRect(_sourceRect), type(_type), behavior(_behavior), theme(_theme), layerType(_layerType){
	}

	Tile(const Tile& other)
    : id(other.id), srcRect(other.srcRect), type(other.type) {
    behavior = other.behavior ? other.behavior->clone() : nullptr;
	}
	Tile& operator=(const Tile& other) {
    if (this != &other) {
        id = other.id;
        srcRect = other.srcRect;
        type = other.type;
        delete behavior;
        behavior = other.behavior ? other.behavior->clone() : nullptr;
    }
    return *this;
}
	Tile(Tile&&) = default; // Allow moving
	Tile& operator=(Tile&&) = default;
	
	/*
	* loi memory ko delete dc..  ;-;
	~Tile() {
		delete behavior;
	}
	*/
};