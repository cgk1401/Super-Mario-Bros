#include "../headers/Map.h"
#include "../headers/ConcreteTileBehavior.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Map::Map(const char* texturePath, int r, int c) {
    texture = LoadTexture(texturePath);
    initMap(r, c);

    tileRows = texture.height / TILE_SIZE;
    tileColumns = texture.width / TILE_SIZE;

    tileSetSourceRects.resize(tileRows);
    //for (auto& t : tileSetSourceRects) {

    //    t.resize(tileColumns);
    //}
    //this is the old method, result in some invisible tiles

    for (int i = 0; i < 8; i += 2) {
		tileSetSourceRects[i].resize(33);
    }
    for (int i = 1; i < 8; i += 2) {
        tileSetSourceRects[i].resize(30);
	}
    for (int i = 8; i < tileRows; i++) {
        tileSetSourceRects[i].resize(24);
    }

    for (int x = 0; x < tileRows; x++) {
        for (int y = 0; y < tileSetSourceRects[x].size(); y++) {
            tileSetSourceRects[x][y] = { (float)y * TILE_SIZE, (float)x * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE };
        }
    }
	//this prevents some invisible tiles

      for (int r = 0; r < tileRows; r++) {
        cout << r <<": ";
        for (int c = 0; c < tileSetSourceRects[r].size(); c++) {
            cout << c <<" " ;
        }
        cout << endl;
        }


    createTileCatalog();
}
Map::~Map(){
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {
            delete mapData[x][y].state;
            mapData[x][y].state = nullptr;
        }
    }
    tileCatalog.clear();
    mapRects.clear();
    mapData.clear();
    UnloadTexture(texture);
}
void Map::initMap(int r, int c) {
    mapRects.clear();
    mapData.clear();

    rows = r;
    columns = c;

    //cout << "column: " << c << endl;;
    mapRects.resize(rows, vector<Rectangle>(columns));
    mapData.resize(rows, vector<MapTileInstance>(columns));

    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {
            // << x << " - " << y << endl;
            mapRects[x][y] = { (float)(y * TILE_SIZE), (float)(x * TILE_SIZE), (float)TILE_SIZE, (float)TILE_SIZE };
            mapData[x][y] = { 0, false };
        }
    }
}

void Map::createTileCatalog() {
    tileCatalog.clear();
    tileCatalog.emplace(0, Tile(0, tileSetSourceRects[0][0], EMPTY, new EmptyTileBehavior())); //EMPTY tile
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 7; j++) {
            tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], GROUND, new SolidTileBehavior())); //Ground tile
        }
		//ground tiles, solid, not breakable, not interactable, no effect (except for cannon head)



        for (int j = 7; j < 9; j++) {
			tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], BRICK, new BrickTileBehavior())); //Brick tile
        }
		//brick tiles, solid, breakable if hit under, no effect



        for (int j = 9; j < 16; j++) {
			tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], DECORATION_BLOCK, new DecorationTileBehavior())); //Decoration tile
        }
		//castle tiles, work as decoration



		tileCatalog.emplace(getTileIDFromCoords(i, 16), Tile(1, tileSetSourceRects[i - 1][16 - 1], PIPE, new SolidTileBehavior())); //Pipe tile
		//pipe tiles, solid, not breakable, not interactable, has pipe effect (add later)



        for (int j = 17; j < 20; j++) {
			tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], DECORATION_BLOCK, new DecorationTileBehavior())); //Decoration tile
        }
		//decoration tiles, work as decoration



		if (i % 2 == 1) tileCatalog.emplace(getTileIDFromCoords(i, 20), Tile(1, tileSetSourceRects[i - 1][20 - 1], QUESTION_BLOCK, new QuestionTileBehavior())); //Question Block tile
		else if (i % 2 == 0) tileCatalog.emplace(getTileIDFromCoords(i, 20), Tile(1, tileSetSourceRects[i - 1][20 - 1], DECORATION_BLOCK, new DecorationTileBehavior())); //Decoration tile
        //invisible question block tile, solid, not breakable, not interactable, has question block effect (add later)
		//decoration tile, work as decoration



        for (int j = 21; j < 24; j++) {
			if (i % 2 == 1) tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], QUESTION_BLOCK, new QuestionTileBehavior())); //Question block tile
			//Question block tiles, solid, not breakable, not interactable, has question block effect (add later)



            else tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], ITEM, new ItemBehavior()));
			//Item tile, not solid, not breakable, disappear when collision with player (effect add later)
        }



        if (i % 2 == 1) tileCatalog.emplace(getTileIDFromCoords(i, 24), Tile(1, tileSetSourceRects[i - 1][24 - 1], USED_QUESTION_BLOCK, new SolidTileBehavior())); //Ground tile
        else if (i % 2 == 0) tileCatalog.emplace(getTileIDFromCoords(i, 24), Tile(1, tileSetSourceRects[i - 1][24 - 1], ITEM, new ItemBehavior())); //Item tile
        //ground tiles, solid, not breakable, not interactable, no effect
        //Item tile, not solid, not breakable, disappear when collision with player (effect add later)



        tileCatalog.emplace(getTileIDFromCoords(i, 25), Tile(1, tileSetSourceRects[i - 1][25 - 1], ITEM, new ItemBehavior())); //Item tile
        //Item tile, not solid, not breakable, disappear when collision with player (effect add later)



        for (int j = 26; j < 29; j++) {
			tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], DECORATION_BLOCK, new DecorationTileBehavior())); //Decoration tile
        }
		//decoration tiles, work as decoration



        tileCatalog.emplace(getTileIDFromCoords(i, 29), Tile(1, tileSetSourceRects[i - 1][29 - 1], LAVA_FLOOR, new DecorationTileBehavior())); //Decoration tile
		//lava floor tile, work as a trap, die when touch, somehow has the same behavior as decoration tile
        


		tileCatalog.emplace(getTileIDFromCoords(i, 30), Tile(1, tileSetSourceRects[i - 1][30 - 1], GROUND, new SolidTileBehavior())); //ground tile
		//ground tile, solid, not breakable, not interactable, the bridge tile has effect (add later)



        for (int j = 30; j < 34; j++) {
            if (i % 2 == 1) {
                tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], GROUND, new SolidTileBehavior())); //Ground tile
            }
            //ground tiles, solid, not breakable, not interactable, no effect
        }
    }
	//catalog for first 8 rows, which follow the origin color palettes (overworld, underground, castle, underwater)




    for (int i = 9; i < 21; i++) {
        for (int j = 1; j < 6; j++) {
            tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], PIPE, new SolidTileBehavior())); //Pipe tiles
        }
        //Pipe 



        for (int j = 6; j < 9; j++) {
            tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], GROUND, new SolidTileBehavior())); //Ground tiles
        }
        //Ground



        for (int j = 9; j < 12; j++) {
            if (i % 2 == 1) tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], GROUND, new SolidTileBehavior())); //Ground tiles
            else if (i % 2 == 0) tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], DECORATION_BLOCK, new DecorationTileBehavior())); //Decoration tiles
        }
        //Ground
        //Decoration



        tileCatalog.emplace(getTileIDFromCoords(i, 12), Tile(1, tileSetSourceRects[i - 1][12 - 1], FINISHING_POLE, new DecorationTileBehavior())); //Ground tiles
        //Finishing pole



        for (int j = 13; j < 19; j++) {
            tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], DECORATION_BLOCK, new DecorationTileBehavior())); //Decoration tiles
        }
        //Decoration


        if ( i % 2 == 0) tileCatalog.emplace(getTileIDFromCoords(i, 19), Tile(1, tileSetSourceRects[i - 1][19 - 1], DECORATION_BLOCK, new DecorationTileBehavior())); //Decoration tiles
        else if ( i % 2 == 1) tileCatalog.emplace(getTileIDFromCoords(i, 19), Tile(1, tileSetSourceRects[i - 1][19 - 1], GROUND, new SolidTileBehavior())); //Solid tiles
        //
        //



        for (int j = 20; j < 25; j++) {
            tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(1, tileSetSourceRects[i - 1][j - 1], DECORATION_BLOCK, new DecorationTileBehavior())); //Decoration tiles
        }
        //Decoration
    }
    //catalog for the rest, which have 6 palettes instead of 4 (add snow and mushroom)




    //tileCatalog.emplace(getTileIDFromCoords(1, 1), Tile(1, tileSetSourceRects[1 - 1][1 - 1], GROUND, new SolidTileBehavior())); //Ground tile
    
    //tileCatalog.emplace(1, Tile(1, tile, ));

    //....


}
bool operator!=(Vector2 v1, Vector2 v2) {
    return v1.x != v2.x || v1.y != v2.y;
}
void Map::update(bool isEditing) {
    float dt = GetFrameTime();
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            int id = mapData[row][col].tileID;
            if (id != 0) {
                //tileCatalog[id].behavior->update(GetFrameTime(), row, col, this, &mapData[row][col]);
               Tile tile = getTile(row, col);

                MapTileInstance* tileInstance = getMapTileInstance(row, col);
                
                //if (!tileInstance || tileInstance->tileID == 0) continue;
                //tile.behavior->update(GetFrameTime(), x, y, map, tileInstance);
                Vector2 ori = { 0, 0 };
             
                if(tile.behavior) tile.behavior->update(dt, row, col, this, tileInstance);
                
            }
        }
    }
}

void Map::draw(bool isEditing) {
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {
            int id = mapData[x][y].tileID;

            auto it = tileCatalog.find(id);
            if (id && it != tileCatalog.end()) {
                Vector2 drawPos = {
                   mapRects[x][y].x + mapData[x][y].offsetPos.x,
                    mapRects[x][y].y + mapData[x][y].offsetPos.y
                };

                Rectangle destRect = { drawPos.x, drawPos.y, TILE_SIZE, TILE_SIZE };
                DrawTexturePro(texture, it->second.srcRect, destRect, { 0,0 }, 0, WHITE);
            }
            if (isEditing) DrawRectangleLinesEx(mapRects[x][y], 0.5f, DARKGRAY);
        }
    }
}

int Map::getTileIDFromCoords(int fileRow, int fileCol) const {
    if (fileRow < 0 || fileRow >= tileRows ||
        fileCol < 0 || fileCol >= tileSetSourceRects[fileRow].size()) {
        TraceLog(LOG_ERROR, "OUT OF RANGE");
        return 0;
    }

    int idOffset = 0;
    for (int r = 0; r < fileRow; ++r) {
        idOffset += tileSetSourceRects[r].size();
    }
    return idOffset + fileCol;
}


Tile Map::getTile(int tileID) const {
    auto it = tileCatalog.find(tileID);
    if (it == tileCatalog.end()) {
        TraceLog(LOG_INFO, "inavailable in catalog");
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
    if (row < 0 || row >= rows || col < 0 || col >= columns) {
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
void Map::removeTile(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= columns) return;

    mapData[row][col].tileID = 0;
    mapData[row][col].hasItem = false;
    mapData[row][col].offsetPos = { 0, 0 };
    
    if (mapData[row][col].state) {
        delete mapData[row][col].state;
        mapData[row][col].state = nullptr;
    }
}

void Map::updateTileInstancePosition(int row, int col, Vector2 offset){
    if (row >= 0 && row < rows && col >= 0 && col < columns) {
        mapData[row][col].offsetPos = offset;
        //cout << mapData[row][col].offsetPos.x << " - " << mapData[row][col].offsetPos.y << endl;
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