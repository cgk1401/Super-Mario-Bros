#pragma once
#include "../headers/Map.h"
#include "../headers/Global.h"
#include "../headers/GameState.h"
#include "../headers/Button.h"

class MapEditor : public Map, public GameState {
private:
    //int selectedTileID = 0;  
    Button* backButton;
    int mapWidth;
    int uiWidth;
    Vector2 dragStartTile = {-1, -1};
    Vector2 dragEndTile = {-1, -1};
    bool isDragging = false;

    vector<vector<Rectangle>> brushBuffer;
    //Button* expandAreaButton;
public:
    MapEditor(const char* path, int r = 13, int c = 100);
    Camera2D camera{};
    Camera2D cameraEditor{};
    bool IsInsideMap(int row, int col);
    void saveToFile(const char* filename);

    //Inherit GameState
    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render() override;
};