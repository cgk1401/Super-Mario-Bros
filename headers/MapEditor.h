#pragma once
#include "../headers/Map.h"
#include "../headers/Global.h"
#include "../headers/GameState.h"
#include "../headers/Button.h"

class MapEditor : public Map, public GameState {
private:
    int selectedTileID = 0;  
    Button* backButton;
    int mapWidth;
    int uiWidth;

public:
    MapEditor(const char* path, int r = 12, int c = 32);
    Camera2D camera{};

    void saveToFile(const char* filename);

    //Inherit GameState
    void handleInput(Game& game) override{}
    void update(Game& game) override;
    void render() override;
};