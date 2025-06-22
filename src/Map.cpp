#include "../headers/Map.h"
#include "../headers/ConcreteTileBehavior.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Map::Map(const char* texturePath, int r, int c) {
    texture = LoadTexture(texturePath);
    initMap(r, c);

    tileRows = texture.width / side;
    tileColumns = texture.height / side;

    tileSetSourceRects.resize(tileRows);
    for (auto& t : tileSetSourceRects) {

        t.resize(tileColumns);
    }
    for (int x = 0; x < tileRows; x++) {
        for (int y = 0; y < tileColumns; y++) {
            tileSetSourceRects[x][y] = { (float)y * side, (float)x * side, (float)side, (float)side };
        }
    }
    createTileCatalog();
}

void Map::initMap(int r, int c) {
    rows = r;
    columns = c;

    mapRects.resize(rows, vector<Rectangle>(columns));
    mapData.resize(rows, vector<MapTileInstance>(columns));

    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {
            mapRects[x][y] = { (float)(y * side), (float)(x * side), (float)side, (float)side };
            mapData[x][y] = { 0, false };
        }
    }
}

void Map::createTileCatalog() {
    tileCatalog.clear();
    tileCatalog.emplace(0, Tile(0, tileSetSourceRects[0][0], EMPTY, new EmptyTileBehavior())); //EMPTY tile
    tileCatalog.emplace(getTileIDFromCoords(1, 1), Tile(1, tileSetSourceRects[1 - 1][1 - 1], GROUND, new SolidTileBehavior())); //Ground tile
    tileCatalog.emplace(getTileIDFromCoords(1, 2), Tile(1, tileSetSourceRects[1 - 1][2 - 1], BRICK, new BrickTileBehavior())); //Ground tile
    //tileCatalog.emplace(1, Tile(1, tile, )));
    
    //....


}
void Map::update(Camera2D& camera,  bool isEditing) {
    
    if (isEditing) {
        float dt = GetFrameTime();
        float speed = 200;

        if (IsKeyDown(KEY_RIGHT)) {
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                speed = 1000;
            }
            camera.target.x += speed * dt;

        }
        if (IsKeyDown(KEY_LEFT)) {
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                speed = 1000;
            }
            camera.target.x -= speed * dt;
        }

        if (camera.target.x < 0) {
            camera.target.x = 0;
        }
    }
}

void Map::draw(Camera2D& camera, bool isEditing) {
    BeginMode2D(camera);
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {
            int id = mapData[x][y].tileID;
            
            auto it = tileCatalog.find(id);
            if ( id && it != tileCatalog.end() ) {
                DrawTexturePro(texture, it->second.srcRect, mapRects[x][y], { 0,0 }, 0, WHITE);
            }
            if (isEditing) DrawRectangleLinesEx(mapRects[x][y], 0.5f, DARKGRAY);
        }
    }
    EndMode2D();
}

int Map::getTileIDFromCoords(int fileRow, int fileCol) const {
    return (fileRow - 1) * tileColumns + fileCol;
}


Tile Map::getTile(int tileID) const {
    auto it = tileCatalog.find(tileID);
    if (it == tileCatalog.end()) {
        return Tile(0, tileSetSourceRects[0][0], EMPTY, tileCatalog.at(0).behavior);
    }
    return Tile(it->second.id, it->second.srcRect, it->second.type, it->second.behavior);
}

Tile Map::getTile(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= columns) {
        return getTile(0); // Return empty tile info for out of bounds
    }
    int tileID = mapData[row][col].tileID;
    return getTile(tileID);
}

MapTileInstance* Map::getMapTileInstance(int row, int col) {
    if (row < 0 || row >= tileRows || col < 0 || col >= tileColumns) {
        return nullptr;
    }
    return &mapData[row][col];
}

void Map::setTile(int row, int col, int tileID) {
    if (row < 0 || row >= rows || col < 0 || col >= columns) {
        return;
    }
    auto it = tileCatalog.find(tileID);
    if (it == tileCatalog.end()) return;

    mapData[row][col].tileID = tileID;
    mapData[row][col].hasItem = false;
    if (it->second.type == QUESTION_BLOCK || it->second.type == COINS_BLOCK) {
        mapData[row][col].hasItem = true;
    }
    
}

void Map::loadFromFile(const char* filename) {
    ifstream MyReadFile(filename);

    if (!MyReadFile.is_open()) {
        cerr << "Error: Could not open map file " << filename << endl;
        return;
    }

    int fileRows, fileCols;
    MyReadFile >> fileRows >> fileCols;

    initMap(fileRows, fileCols); // Re-initialize map with new dimensions

    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {
            string s;
            MyReadFile >> s;
            int commaPos = s.find(',');
            if (commaPos == string::npos) { // No comma, treat as single TileID
                try {
                    int tileID = stoi(s);
                    setTile(x, y, tileID);
                }
                catch (const invalid_argument& ia) {
                    cerr << "Invalid TileID in map file: " << s << " at (" << x << "," << y << ")" << endl;
                    setTile(x, y, 0); // Default to empty
                }
                catch (const out_of_range& oor) {
                    cerr << "TileID out of range in map file: " << s << " at (" << x << "," << y << ")" << endl;
                    setTile(x, y, 0); // Default to empty
                }
            }
            else {
                try {
                    int tileX = stoi(s.substr(0, commaPos));
                    int tileY = stoi(s.substr(commaPos + 1));
                    // Convert (tileX, tileY) from file (1-based) to our TileID
                    int tileID = getTileIDFromCoords(tileX, tileY);
                    setTile(x, y, tileID);
                }
                catch (const invalid_argument& ia) {
                    cerr << "Invalid texture coordinates in map file: " << s << " at (" << x << "," << y << ")" << endl;
                    setTile(x, y, 0); // Default to empty
                }
                catch (const out_of_range& oor) {
                    cerr << "Texture coordinates out of range in map file: " << s << " at (" << x << "," << y << ")" << endl;
                    setTile(x, y, 0); // Default to empty
                }
            }
        }
    }
    cout << "Loaded file successfully: " << filename << endl;
    MyReadFile.close();
}