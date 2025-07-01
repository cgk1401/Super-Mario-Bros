#pragma once
#include "../headers/Tile.h"
#include "raylib.h"
#include <map>
#include <vector>
#include <memory>
using namespace std;

struct TileState;

struct MapTileInstance {
	int tileID;
    Vector2 offsetPos = { 0, 0 };
	bool hasItem;

    TileState* state = nullptr;

};


class Map {
protected:
	Texture2D texture;								                //Tileset texture
	map<int, Tile> tileCatalog;					                    //Kho luu tru cac tile (1 dạng của Flyweight pattern)
	vector<vector<Rectangle>> mapRects;				                //Tọa độ từng ô
	vector<vector<MapTileInstance>> mapData;		                //data của từng ô: 0 0 1 0 -> 0: empty tile, 1: brick tile,...
	vector<vector<Rectangle>> tileSetSourceRects;	                //Lưu srcRect của từng tile trong tileSet
    void createTileCatalog();
public:
    int rows = 12, columns = 16;
    int tileRows, tileColumns; 
    static constexpr int TILE_SIZE = 64;

    Map(const char* path, int r = 12, int c = 32);
    ~Map();
    void initMap(int r, int c);
    void update(bool isEditing = false);
    void loadFromFile(const char* filename);
    void draw(bool isEditing = false);

    Tile getTile(int tileID) const; 
    Tile getTile(int row, int col) const;
    int getTileIDFromCoords(int fileRow, int fileCol) const;
    MapTileInstance* getMapTileInstance(int row, int col);          //Để sau có thể thay đổi trực tiếp từng tile nếu có collision(vd: khi mario nhảy chạm đầu vào block -> block bị nảy lên 1 tí,...)
    void updateTileInstancePosition(int tileRow, int tileCol, Vector2 offset);
 
    void setTile(int row, int col, int tileID);
    void removeTile(int row, int col);
};