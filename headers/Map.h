#pragma once
#include "../headers/Tile.h"
#include "../headers/Global.h"
#include "../headers/Animation.h"
#include "raylib.h"
#include <map>
#include <vector>
#include <memory>
#include <functional>
using namespace std;

struct TileState;

struct MapTileInstance {
	int tileID;
    Vector2 offsetPos = { 0, 0 };
	bool hasItem;

    TileState* state = nullptr;

};


class Map {
    friend class Collision;
protected:
	Texture2D texture;								                //Tileset texture
    Texture2D bricks_texture;
	map<int, Tile> tileCatalog;					                    //Kho luu tru cac tile (1 dạng của Flyweight pattern)
	vector<vector<Rectangle>> mapRects;				                //Tọa độ từng ô
	vector<vector<MapTileInstance>> mapData;		                //data của từng ô: 0 0 1 0 -> 0: empty tile, 1: brick tile,...
	vector<vector<Rectangle>> tileSetSourceRects;	                //Lưu srcRect của từng tile trong tileSet

    map<TileType, Animation> tileAnimation;
    void createTileCatalog();
    void createTileAnimation();
    function<void(EnemyType, Vector2)> spawnEnemyCallback;

    pair<int, int> level;
public:
    int rows = 12, columns = 16;
    int tileRows, tileColumns; 
    static constexpr int TILE_SIZE = 64;

    Map(int r = 12, int c = 32);
    virtual ~Map();
    void initMap(int r, int c);
    void update(bool isEditing = false);
    void loadFromFile(pair<int, int> level, bool isEditing = false);
    void draw(bool isEditing = false);

    Tile getTile(int tileID) const; 
    Tile getTile(int row, int col) const;
    int getTileIDFromCoords(int fileRow, int fileCol) const;
    MapTileInstance* getMapTileInstance(int row, int col);    
    void updateTileInstancePosition(int tileRow, int tileCol, Vector2 offset);

    
    void setEnemySpawnCallback(std::function<void(EnemyType, Vector2)> callback);
    EnemyType getEnemyType(int tileID);

    void setTile(int row, int col, int tileID);
    void removeTile(int row, int col);
};