#include "../headers/MapEditor.h"
#include <iostream>
#include <fstream>
#include "../headers/Game.h"
#include "../headers/MenuState.h"
#include "../headers/TileBehavior.h"
using namespace std;

MapEditor::MapEditor(const char* path, int r, int c) : Map(path, r, c) {
    camera.offset = { 0,0 };
    camera.target = { 0, 0 };
    camera.rotation = 0;
    camera.zoom = 1.0;

    mapWidth = screenWidth * 0.75f;
    uiWidth = screenWidth - (int)mapWidth;

    backButton = new Button("../assets/GUI/Button.png", 10, 10 , screenWidth / 3 * 0.5f, screenHeight * 0.15f * 0.5f, "HOME", WHITE);
}

void MapEditor::saveToFile(const char* filename) {
    ofstream MyFile(filename);

    if (!MyFile.is_open()) {
        cerr << "Error: Could not open file for saving: " << filename << endl;
        return;
    }

    MyFile << rows << " " << columns << "\n";
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {
            // Save TileID directly
            MyFile << mapData[x][y].tileID; // Access tileID from MapTileInstance
            if (y < columns - 1) MyFile << " ";
        }
        MyFile << endl;
    }

    cout << "Saved file successfully: " << filename << endl;
    MyFile.close();
}

void MapEditor::render() {
   
    BeginScissorMode(0, 0, screenWidth * 0.75f, screenHeight);
    Map::draw(camera, true); // Draw map with grid lines
    EndScissorMode();

    int uiStartX = mapWidth;

    DrawRectangle(uiStartX, 0, uiWidth, screenHeight, LIGHTGRAY);
    DrawText("Tileset:", uiStartX + 10, 10, 20, BLACK);

    int currentY = 40; 
    for (int r = 0; r < tileRows; r++) {
        for (int c = 0; c < tileColumns; c++) {
            Rectangle tileSrc = tileSetSourceRects[r][c];
            Rectangle tileDest = { (float)uiStartX + 10 + (float)c * (side + 4), (float)currentY + (float)r * (side + 4), (float)side, (float)side };

            DrawTexturePro(texture, tileSrc, tileDest, { 0,0 }, 0, WHITE);

            int currentTileID = getTileIDFromCoords(r + 1, c + 1);

            if (CheckCollisionPointRec(GetMousePosition(), tileDest) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                selectedTileID = currentTileID;
                cout << "Selected Tile ID: " << selectedTileID << " (Tileset coords: " << r + 1 << "," << c + 1 << ")\n";
            }

            // Highlight tile đã chọn
            if (selectedTileID == currentTileID) {
                DrawRectangleLinesEx(tileDest, 2, RED);  // highlight
            }
        }
    }

    // Draw currently selected tile info
    uiStartX = 10;
    DrawText("Selected:", uiStartX + 10, screenHeight * 0.2f - 60, 20, BLACK);
    if (selectedTileID != 0) {
        Tile currentSelectedInfo = getTile(selectedTileID);
        DrawTexturePro(texture, currentSelectedInfo.srcRect, { (float)uiStartX + 110, (float)screenHeight * 0.2f - 60, 40, 40 }, { 0,0 }, 0, WHITE);
      
        DrawText(TextFormat("Type: %d", currentSelectedInfo.type), uiStartX + 10, screenHeight * 0.2f - 20, 15, BLACK);
    }
    else {
        DrawText("None", uiStartX + 110, screenHeight * 0.2f - 60, 20, BLACK);
    }

    backButton->draw();
}

void MapEditor::update(Game& game) {
    Map::update(camera); // Update camera movement

    int uiStartX = mapWidth;
    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);

    // Check if mouse is over the map area (not UI)
    Rectangle mapDrawingArea = { 0, 0, (float)mapWidth, (float)screenHeight };
    if (CheckCollisionPointRec(GetMousePosition(), mapDrawingArea)) {
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < columns; y++) {
                if (CheckCollisionPointRec(mouseWorld, mapRects[x][y])) {
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                        setTile(x, y, selectedTileID);
                        Tile t = getTile(selectedTileID);
                        cout << t.id << endl;
                    }
                    else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
                        setTile(x, y, 0);
                    }
                }
            }
        }
    }
    backButton->update();
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S))
        saveToFile("map1.txt");

    if (IsKeyDown(KEY_LEFT_CONTROL ) && IsKeyPressed(KEY_L))
        loadFromFile("map1.txt");

    if (backButton->IsClicked()) {
        game.changeState(new MenuState());
    }
}