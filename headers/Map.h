#pragma once
#include "../headers/Tile.h"
#include "../headers/Global.h"
#include "../headers/Animation.h"
#include "FireBar.h"
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
    TileState* state = nullptr;

};

struct Layer {
    LayerType type;
    bool visible = true;                            
    bool hasCollision = false;           
    vector<vector<MapTileInstance>> mapData;         
    vector<vector<MapTileInstance>> mapData_first; 
};


class Map {
    friend class Collision;
protected:
	Texture2D texture;								                //Tileset texture
    Texture2D bricks_texture;

	map<int, Tile> tileCatalog;					                    //Kho luu tru cac tile (1 dạng của Flyweight pattern)
	vector<vector<Rectangle>> mapRects;				                //Tọa độ từng ô
	//vector<vector<MapTileInstance>> mapData;		                //data của từng ô: 0 0 1 0 -> 0: empty tile, 1: brick tile,...
    vector<Layer> layers;
	vector<vector<Rectangle>> tileSetSourceRects;	                //Lưu srcRect của từng tile trong tileSet

    map<TileType, Animation> tileAnimation;
    void createTileCatalog();
    void createTileAnimation();
    function<void(EnemyType, Vector2, MapTheme)> spawnEnemyCallback;

    pair<int, int> level = {1,1};
    MapTheme maptheme;

    // vector<vector<MapTileInstance>> mapData_first;
    //vector<FireBar*> firebars;
public:
    int rows = 12, columns = 16;
    int tileRows, tileColumns; 
    static constexpr int TILE_SIZE = 64;
    const int numberLayers = 5;

    Map(pair<int, int> level = {1,1},int r = 12, int c = 32);
    virtual ~Map();
    void initMap(int r, int c);
    void update(bool isEditing = false);
    void loadFromFile(pair<int, int> level, bool isEditing = false);
    void draw(bool isEditing = false);
    void drawLayer(LayerType layertype);
    
    Tile getTile(int tileID) const; //tile catalog
    Tile getTile(int row, int col, LayerType layerType) const; //world
    int getTileIDFromCoords(int fileRow, int fileCol) const;
    MapTileInstance* getMapTileInstance(int row, int col, LayerType layerType);    
    void updateTileInstancePosition(int tileRow, int tileCol, Vector2 offset, LayerType layerType);
    MapTheme getMapTheme(pair<int, int> level);
    
    void setEnemySpawnCallback(std::function<void(EnemyType, Vector2, MapTheme)> callback);
    EnemyType getEnemyType(int ID);

    void setTile(int row, int col, int tileID, int layerIndex);
    void removeTile(int row, int col);
    
    pair<int, int> getLevel();
    void refactorMapTXT(const char* filename);

};