#include "../headers/Map.h"
#include "../headers/ConcreteTileBehavior.h"
#include "../headers/Global.h"
#include "../headers/ItemManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <functional>
using namespace std;
#define MAX_COLUMN 220

Map::Map(pair<int, int> _level, int r, int c) {
    texture =  LoadTexture("../assets/Map/tileset_gutter64x64.png");
    bricks_texture = LoadTexture("../assets/Map/bricks.png");
    level = _level;
    
    initMap(r, c);

    tileRows = texture.height / TILE_SIZE;
    tileColumns = texture.width / TILE_SIZE;

    tileSetSourceRects.resize(tileRows);
    //cout << "tileRows: " << tileRows << endl;
    //for (auto& t : tileSetSourceRects) {

    //    t.resize(tileColumns);
    //}
    //this is the old method, result in some invisible tiles

    for (int i = 0; i < 8; i += 2) {
		tileSetSourceRects[i].resize(30);
    }
    for (int i = 1; i < 8; i += 2) {
        tileSetSourceRects[i].resize(27);
	}
    for (int i = 8; i < 20; i++) {
        tileSetSourceRects[i].resize(24);
    }

    for (int i = 20; i < tileRows; i++) {
        if (i == 22) tileSetSourceRects[i].resize(10);
        else tileSetSourceRects[i].resize(13);
    }

    for (int x = 0; x < tileRows; x++) {
        for (int y = 0; y < tileSetSourceRects[x].size(); y++) {
            tileSetSourceRects[x][y] = { (float)y * TILE_SIZE, (float)x * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE };
        }
    }
	//this prevents some invisible tiles
    createTileCatalog();
    createTileAnimation();

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
    mapData_first.clear();

    rows = r;
    columns = c;

    mapRects.resize(rows, vector<Rectangle>(columns));
    mapData.resize(rows, vector<MapTileInstance>(columns));
    mapData_first.resize(rows, vector<MapTileInstance>(columns));

    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {
            // << x << " - " << y << endl;
            mapRects[x][y] = { (float)(y * TILE_SIZE), (float)(x * TILE_SIZE), (float)TILE_SIZE, (float)TILE_SIZE };
            mapData[x][y] = { 0, false };
        }
    }

    mapData_first = mapData;
}

void Map::createTileAnimation() {
    Animation questionBlock_animation;
    for (int i = 0; i < 3; i++)
    {
        questionBlock_animation.frame.push_back({ 80 + (float)i * 16, 112, 16, 16 });
    }
    questionBlock_animation.durationtime = 0.2f;
    tileAnimation.emplace(TileType::QUESTION_BLOCK, questionBlock_animation);

}

void Map::createTileCatalog() {
    tileCatalog.clear();
    tileCatalog.emplace(0, Tile(0, tileSetSourceRects[0][0], EMPTY, new EmptyTileBehavior())); //EMPTY tile

    array<MapTheme, 4> themes = {
        MapTheme::OVERWORLD,
        MapTheme::UNDERGROUND,
        MapTheme::CASTLE,
        MapTheme::UNDERWATER
    };
    for (int i = 1; i < 3; i++) {
        for (MapTheme theme : themes) {
            int themeOffset = static_cast<int>(theme) * 2;

            for (int j = 1; j < 7; j++) {
                tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, j), Tile(getTileIDFromCoords(i + themeOffset, j), tileSetSourceRects[i + themeOffset - 1][j - 1], j == 5 ? USED_QUESTION_BLOCK : GROUND, new SolidTileBehavior(), theme)); //Ground tile
            }

            for (int j = 7; j < 9; j++) {
                tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, j), Tile(getTileIDFromCoords(i + themeOffset, j), tileSetSourceRects[i + themeOffset- 1][j - 1], BRICK, new BrickTileBehavior(), theme)); //Brick tile
            }

            for (int j = 9; j < 16; j++) {
                if(j == 14) tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, j), Tile(getTileIDFromCoords(i + themeOffset, j), tileSetSourceRects[i + themeOffset - 1][j - 1], BLACK_BLOCK, new DecorationTileBehavior(), theme)); //Decoration tile
                else
                tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, j), Tile(getTileIDFromCoords(i + themeOffset, j), tileSetSourceRects[i + themeOffset - 1][j - 1], DECORATION_BLOCK, new DecorationTileBehavior(), theme)); //Decoration tile
            }

            tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, 16), Tile(getTileIDFromCoords(i + themeOffset, 16), tileSetSourceRects[i + themeOffset - 1][16 - 1], PIPE, new SolidTileBehavior(), theme)); //Pipe tile

            for (int j = 17; j < 20; j++) {
                tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, j), Tile(getTileIDFromCoords(i + themeOffset, j), tileSetSourceRects[i + themeOffset - 1][j - 1], DECORATION_BLOCK, new DecorationTileBehavior(), theme)); //Decoration tile
            }

            if (i % 2 == 1) tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, 20), Tile(getTileIDFromCoords(i + themeOffset, 20), tileSetSourceRects[i + themeOffset - 1][20 - 1], QUESTION_BLOCK, new QuestionTileBehavior(), theme)); //Question Block tile
            else if (i % 2 == 0) tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, 20), Tile(getTileIDFromCoords(i + themeOffset, 20), tileSetSourceRects[i + themeOffset - 1][20 - 1], STAR_BRICK, new QuestionTileBehavior(), theme)); //Decoration tile
            ///////// The brick which has the star

            for (int j = 21; j < 22; j++) {
                if (i % 2 == 0) tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, j), Tile(getTileIDFromCoords(i + themeOffset, j), tileSetSourceRects[i + themeOffset - 1][j - 1], COIN, new DecorationTileBehavior(), theme));
                if (i % 2 == 1) {
                    tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, j), Tile(getTileIDFromCoords(i + themeOffset, j), tileSetSourceRects[i + themeOffset - 1][j - 1], QUESTION_BLOCK, new QuestionTileBehavior(), theme));
                    tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, j + 1), Tile(getTileIDFromCoords(i + themeOffset, j), tileSetSourceRects[i + themeOffset- 1][j + 1 - 1], FIREBAR_BLOCK, new SolidTileBehavior(), theme));
                }
            }

            for (int j = 23; j < 26; j++) {
                tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, j), Tile(getTileIDFromCoords(i + themeOffset, j), tileSetSourceRects[i + themeOffset - 1][j - 1], DECORATION_BLOCK, new DecorationTileBehavior(), theme)); //Decoration tile
            }

            tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, 26), Tile(getTileIDFromCoords(i + themeOffset, 26), tileSetSourceRects[i + themeOffset - 1][26 - 1], LAVA_FLOOR, new DecorationTileBehavior(), theme)); //Decoration tile

            tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, 27), Tile(getTileIDFromCoords(i + themeOffset, 27), tileSetSourceRects[i + themeOffset - 1][27 - 1], GROUND, new SolidTileBehavior(), theme)); //ground tile

            if (i % 2 == 1) {
                for (int j = 28; j < 31; j++) {
                    tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, j), Tile(getTileIDFromCoords(i + themeOffset, j), tileSetSourceRects[i + themeOffset - 1][j - 1], GROUND, new SolidTileBehavior(), theme)); //Ground 
                }
            }
        }
    }
	//catalog for first 8 rows, which follow the origin color palettes (overworld, underground, castle, underwater)



    for (int i = 9; i < 21; i++) {
        for (int j = 1; j < 6; j++) {
            tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(getTileIDFromCoords(i, j), tileSetSourceRects[i - 1][j - 1], PIPE, new SolidTileBehavior())); //Pipe tiles
        }

        for (int j = 6; j < 9; j++) {
            tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(getTileIDFromCoords(i, j), tileSetSourceRects[i - 1][j - 1], GROUND, new SolidTileBehavior())); //Ground tiles
        }

        for (int j = 9; j < 12; j++) {
            if (i % 2 == 1) tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(getTileIDFromCoords(i, j), tileSetSourceRects[i - 1][j - 1], GROUND, new SolidTileBehavior())); //Ground tiles
            else if (i % 2 == 0) tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(getTileIDFromCoords(i, j), tileSetSourceRects[i - 1][j - 1], DECORATION_BLOCK, new DecorationTileBehavior())); //Decoration tiles
        }

        tileCatalog.emplace(getTileIDFromCoords(i, 12), Tile(getTileIDFromCoords(i, 12), tileSetSourceRects[i - 1][12 - 1], FINISHING_POLE, new DecorationTileBehavior())); //Ground tiles

        for (int j = 13; j < 19; j++) {
            tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(getTileIDFromCoords(i, j), tileSetSourceRects[i - 1][j - 1], DECORATION_BLOCK, new DecorationTileBehavior())); //Decoration tiles
        }

        if ( i % 2 == 0) tileCatalog.emplace(getTileIDFromCoords(i, 19), Tile(getTileIDFromCoords(i, 19), tileSetSourceRects[i - 1][19 - 1], DECORATION_BLOCK, new DecorationTileBehavior())); //Decoration tiles
        else if ( i % 2 == 1) tileCatalog.emplace(getTileIDFromCoords(i, 19), Tile(getTileIDFromCoords(i, 19), tileSetSourceRects[i - 1][19 - 1], GROUND, new SolidTileBehavior())); //Solid tiles

        for (int j = 20; j < 25; j++) {
            tileCatalog.emplace(getTileIDFromCoords(i, j), Tile(getTileIDFromCoords(i, j), tileSetSourceRects[i - 1][j - 1], DECORATION_BLOCK, new DecorationTileBehavior())); //Decoration tiles
        }
        //Decoration
    }
    //catalog for the rest, which have 6 palettes instead of 4 (add snow and mushroom)

    for (int i = 21; i <= 21; i++) {
        for(auto& theme: themes){
            int themeOffset = static_cast<int>(theme);
            for (int j = 1; j < 11; j++) {
                tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, j), Tile(getTileIDFromCoords(i + themeOffset, j), tileSetSourceRects[i + themeOffset- 1][j - 1], ENEMY, new DecorationTileBehavior(), theme)); //Ground tiles
            }

            for (int j = 11; j < 14; j++) {
                if (themeOffset != 2) tileCatalog.emplace(getTileIDFromCoords(i + themeOffset, j), Tile(getTileIDFromCoords(i + themeOffset , j), tileSetSourceRects[i + themeOffset - 1][j - 1], ENEMY, new DecorationTileBehavior(), theme)); //Ground tiles
            }
        }
    }
    //temporary enemies to add to map

 

    //tileCatalog.emplace(getTileIDFromCoords(1, 1), Tile(1, tileSetSourceRects[1 - 1][1 - 1], GROUND, new SolidTileBehavior())); //Ground tile
    //tileCatalog.emplace(1, Tile(1, tile, ));


}
bool operator!=(Vector2 v1, Vector2 v2) {
    return v1.x != v2.x || v1.y != v2.y;
}
void Map::update(bool isEditing) {
    float dt = GetFrameTime();
    for(auto& [type, animation] : tileAnimation){
        animation.Update(dt);
    }

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
     Color bgColor = Color{92, 148, 252};
     if(isEditing == false)
        {
            if(level == pair{1,2} || level == pair{1,4}) bgColor = {0,0,0};
        }
    ClearBackground(bgColor);
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {
            int id = mapData[x][y].tileID;

            auto it = tileCatalog.find(id);
            if (id && it != tileCatalog.end()) {
                Texture2D tileTexture = texture;
                Rectangle src = it->second.srcRect;

                if ((it->second.type == ENEMY || it->second.type == TileType::COIN) && isEditing == false) continue;
                else if(it->second.type ==  TileType::QUESTION_BLOCK){
                    src = tileAnimation.at(TileType::QUESTION_BLOCK).getcurrentframe();
                    src.y +=  (float) it->second.theme * 16.0f;
                    tileTexture = bricks_texture;
                }
                else if(it->second.type == TileType::STAR_BRICK){
                    src = {272, 192  + (float) it->second.theme * 16.0f, 16, 16};
                    tileTexture = bricks_texture;
                }

                Vector2 drawPos = {
                   mapRects[x][y].x + mapData[x][y].offsetPos.x,
                    mapRects[x][y].y + mapData[x][y].offsetPos.y
                };

                Rectangle destRect = { drawPos.x, drawPos.y, TILE_SIZE, TILE_SIZE };
                DrawTexturePro(tileTexture, src, destRect, { 0,0 }, 0, WHITE);
            }
            if (isEditing)
                //Draw grid lines
                DrawRectangleLines(mapRects[x][y].x,
                    mapRects[x][y].y,
                    TILE_SIZE,
                    TILE_SIZE, 
                    BLACK);
        }
    }
}

int Map::getTileIDFromCoords(int fileRow, int fileCol) const {
    fileRow--;
    if (fileRow < 0 || fileRow >= tileRows ||
        fileCol-1 < 0 || fileCol-1 >= tileSetSourceRects[fileRow].size()) {
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
    return Tile(it->second.id, it->second.srcRect, it->second.type, it->second.behavior, it->second.theme);
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

void Map::setEnemySpawnCallback(function<void(EnemyType, Vector2, MapTheme)> callback) {
    spawnEnemyCallback = callback;
}

EnemyType Map::getEnemyType(int ID) {
   for(int i = 21; i <= tileSetSourceRects.size(); i++){
       for(int j = 1 ; j <= tileSetSourceRects[i - 1].size(); j++){
            if(j == 1  && ID == getTileIDFromCoords(i, j)) return EnemyType::GOOMBA;
            else if(j== 3 && ID == getTileIDFromCoords(i, j)) return EnemyType::KOOPA;
            else if(j== 4 && ID == getTileIDFromCoords(i, j)) return EnemyType::PIRANT_PLANT;
        }
   }

   return EnemyType::None;
}
void Map::setTile(int row, int col, int tileID) {
    if (row < 0 || row >= rows || col < 0 || col >= columns) {
        return;
    }

    //if ( mapData[row][col].tileID == tileID) return;
    //cout << tileID << endl;
    auto it = tileCatalog.find(tileID);
    if (it == tileCatalog.end()) {
        TraceLog(LOG_ERROR, "INVALID ID");
        return;
    }
    if (it->second.type == ENEMY) {
        //mapData[row][col].tileID = 0;

        if (spawnEnemyCallback) {
            EnemyType enemyType = getEnemyType(tileID);
            if(enemyType == EnemyType::None) {
                TraceLog(LOG_ERROR, "Invalid enemy");
                return;
            }
            Vector2 spawnPos = {
                static_cast<float>(col * TILE_SIZE),
                static_cast<float>(row * TILE_SIZE)
            };
            spawnEnemyCallback(enemyType, spawnPos, it->second.theme);
        }
    }
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


void Map::loadFromFile(pair<int, int> level, bool isEditing) {
    string filename;
    filename = "map" + to_string(level.first) + "_" + to_string(level.second) + ".txt"; //e.g. map1_1.txt, map1_2.txt

    ifstream MyReadFile(filename);

    if (!MyReadFile.is_open()) {
        cerr << "Error: Could not open map file " << filename << endl;
        return;
    }

    int fileRows, fileCols;
    MyReadFile >> fileRows >> fileCols;
    //cout << fileCols << endl;
    int loadCols = isEditing ? MAX_COLUMN : fileCols;
    initMap(fileRows, loadCols); // Re-initialize map with new dimensions
    columns = loadCols;

    cout << "FILE COLS: " << fileCols << endl;
   
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < fileCols; y++) {
            string s;
            MyReadFile >> s;
            int commaPos = s.find(',');

            if (commaPos == string::npos) {
                try {
                    int tileID = stoi(s);
                    setTile(x, y, tileID);
                    int id = mapData[x][y].tileID;
                    auto it = tileCatalog.find(id);
                    if (id && it != tileCatalog.end()) {
                        if(it->second.type == TileType::COIN){
                            Singleton<ItemManager>::getInstance().Spawn(ItemType::COIN, {(float) y * TILE_SIZE, (float) x * TILE_SIZE});
                        }
                        else if(it->second.type == TileType::FIREBAR_BLOCK){
                            Singleton<ItemManager>::getInstance().Spawn(ItemType::FIRE_BAR, {(float) y * TILE_SIZE + TILE_SIZE / 3, (float) x * TILE_SIZE + TILE_SIZE / 3});
                        }
                    }
                }
                catch (...) {
                    cerr << "Invalid TileID in map file: " << s << " at (" << x << "," << y << ")" << endl;
                    setTile(x, y, 0);
                }
            }
            else {
                try {
                    int tileX = stoi(s.substr(0, commaPos));
                    int tileY = stoi(s.substr(commaPos + 1));
                    int tileID = getTileIDFromCoords(tileX, tileY);
                    setTile(x, y, tileID);
                }
                catch (...) {
                    cerr << "Invalid texture coordinates in map file: " << s << " at (" << x << "," << y << ")" << endl;
                    setTile(x, y, 0);
                }
            }
        }

        if (isEditing) {
            for (int y = fileCols; y < MAX_COLUMN; y++) {
                setTile(x, y, 0);
            }
        }
    }

    mapData_first = mapData;
    std::cout << "Loaded file successfully: " << filename << endl;
    MyReadFile.close();
}


MapTheme Map::getMapTheme(pair<int, int> level){
    if(level == pair{1,2}) return MapTheme::UNDERGROUND;

}

pair<int, int> Map::getLevel() {
    return level;
}
