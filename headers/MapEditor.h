#pragma once
#include "../headers/Map.h"
#include "../headers/Global.h"
#include "../headers/GameState.h"
#include "../headers/Button.h"
#include "../headers/Timer.h"

enum class EditorMode {
    DRAW,
    ERASE
};

class MapEditor : public Map, public GameState {
private:
    //int selectedTileID = 0;  
    Button* back_button;
    vector<Button*> option_buttons;
    Button* tilePicking_button;
    Button* eraserTool_button;
    Button* save_button;
    Button* uploadFile_button;

    Timer saveFileNoti_timer;
    EditorMode editType;

    bool _option_buttons = false;
    int mapWidth;
    int uiWidth;
    Vector2 dragStartTile = {-1, -1};
    Vector2 dragEndTile = {-1, -1};
    bool isDragging = false;

    vector<vector<Rectangle>> brushBuffer;

    Texture2D world_1_1, 
              world_1_2, world_1_2_A, world_1_2_B,
              world_1_3,
              world_1_4;

    pair<int, int> level = {1,1};
public:
    MapEditor(pair<int, int> level  = {1,1},int r = 13, int c = 220);
    ~MapEditor();
    Camera2D camera{};
    Camera2D cameraEditor{};
    bool IsInsideMap(int row, int col);
    void saveToFile();
    void saveMapToJSON(const char* filename);
    Texture2D getTextureByLevel(pair<int, int> _level) const;
    //Inherit GameState
    void update(float deltatime) override;
    void render() override;

    void handleInput();
};