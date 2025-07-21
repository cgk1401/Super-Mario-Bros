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
    Button* backButton;
    vector<Button*> optionButtons;
    Button* tilePickingButton;
    Button* eraserToolButton;
    Timer timer;
    EditorMode editType;

    bool _optionButtons = false;
    int mapWidth;
    int uiWidth;
    Vector2 dragStartTile = {-1, -1};
    Vector2 dragEndTile = {-1, -1};
    bool isDragging = false;

    vector<vector<Rectangle>> brushBuffer;
public:
    MapEditor(const char* path, int r = 13, int c = 100);
    Camera2D camera{};
    Camera2D cameraEditor{};
    bool IsInsideMap(int row, int col);
    void saveToFile(const char* filename);

    //Inherit GameState
    void update(float deltatime) override;
    void render() override;

    void handleInput();
};