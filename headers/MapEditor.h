#pragma once
#include "../headers/Map.h"
#include "../headers/Global.h"
#include "../headers/GameState.h"
#include "../headers/Button.h"
#include "../headers/Timer.h"
#include "SaveConfirmationDialog.h"

enum class EditorMode {
    DRAW,
    ERASE
};

class MapEditor : public Map, public GameState {
private:
    //int selectedTileID = 0;  
    Button* back_button; //nút home
    vector<Button*> option_buttons;
    Button* tilePicking_button;
    Button* eraserTool_button;
    Button* save_button;
    
    Timer saveFileNoti_timer;
    EditorMode editType;

    bool _option_buttons = false;
    int mapWidth;
    int uiWidth;
    Vector2 dragStartTile = {-1, -1};
    Vector2 dragEndTile = {-1, -1};
    bool isDragging = false;

    vector<vector<Rectangle>> brushBuffer;

    Texture2D world_1_1_test;

public:
    MapEditor(int r = 13, int c = 220);
    Camera2D camera{};
    Camera2D cameraEditor{};
    bool IsInsideMap(int row, int col);
    void saveToFile(pair<int, int> level);
    void saveMapToJSON(const char* filename);

    //Inherit GameState
    void update(float deltatime) override;
    void render() override;

    void handleInput();

};