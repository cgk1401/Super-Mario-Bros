#include "../headers/MapEditor.h"
#include <iostream>
#include <fstream>
#include "../headers/Game.h"
#include "../headers/MenuState.h"
#include "../headers/TileBehavior.h"
#include "raymath.h"
using namespace std;

MapEditor::MapEditor(const char* path, int r, int c) : Map(path, r, c) {
    camera.offset = { 0,0 };
    camera.target = { 0, 0 };
    camera.rotation = 0;
    camera.zoom = 1.0;

    cameraEditor.offset = {0,0 };
    cameraEditor.target = { (float) mapWidth, 0 };
    cameraEditor.rotation = 0;
    cameraEditor.zoom = 1.0;

    mapWidth = screenWidth * 0.7f;
    uiWidth = screenWidth - (int)mapWidth;

    backButton = new Button("../assets/GUI/Button.png", 10, 10 , screenWidth / 3 * 0.5f, screenHeight * 0.15f * 0.5f, "HOME", WHITE);
    //expandAreaButton = new Button(mapWidth - 20, screenHeight / 2 - 35, 40, 70, "||", LIGHTGRAY, GRAY, WHITE);
}

void MapEditor::saveToFile(const char* filename) {
    ofstream MyFile(filename);

    if (!MyFile.is_open()) {
        cerr << "Error: Could not open file for saving: " << filename << endl;
        return;
    }
    
  
    int limitCol = 0;
    for (int y = columns - 1; y >= 0; y--) {
        for (int x = 0; x < rows; x++) {
            if (mapData[x][y].tileID != 0) {
                limitCol = y;
                goto found;
            }
        }
    }
    found:


    cout << "Limit column: "<< limitCol <<endl;

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
    //Tile map
    BeginScissorMode(0, 0, screenWidth * 0.75f, screenHeight);
    BeginMode2D(camera);
    Map::draw(true); // Draw map with grid lines
    EndMode2D();
    EndScissorMode();

    
    int uiStartX = mapWidth;

    DrawRectangle(uiStartX, 0, uiWidth, screenHeight, LIGHTGRAY);
    DrawText("Tileset:", uiStartX + 10, 10, 20, BLACK);

    int currentY = 40; 

    Vector2 mouseEditorWorld = GetScreenToWorld2D(GetMousePosition(), cameraEditor);
    BeginMode2D(cameraEditor);
    for (int r = 0; r < tileRows; r++) {
        for (int c = 0; c < tileSetSourceRects[r].size(); c++) {
            Rectangle tileSrc = tileSetSourceRects[r][c];
            Rectangle tileDest = { (float)uiStartX + 10 + (float)c * (TILE_SIZE + 4), (float)currentY + (float)r * (TILE_SIZE + 4), (float)TILE_SIZE, (float)TILE_SIZE };

            DrawTexturePro(texture, tileSrc, tileDest, { 0,0 }, 0, WHITE);

            int currentTileID = getTileIDFromCoords(r + 1, c + 1);

            if (CheckCollisionPointRec(mouseEditorWorld, tileDest) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                selectedTileID = currentTileID;
                cout << "Selected Tile ID: " << selectedTileID << " (Tileset coords: " << r + 1 << "," << c + 1 << ")\n";
            }

            // Highlight tile đã chọn
            if (selectedTileID == currentTileID) {
                DrawRectangleLinesEx(tileDest, 2, RED);  // highlight
            }
        }
    }
    EndMode2D();
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
    //expandAreaButton->draw();
}

void MapEditor::update(Game& game) {
    Map::update(true); // Update camera movement
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

 
    uiWidth = screenWidth - (int)mapWidth;
    int uiStartX = mapWidth;
    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);

    // Check if mouse is over the map area
     float wheel = GetMouseWheelMove();
    Vector2 mousePos = GetMousePosition();
    Rectangle mapDrawingArea = { 0, 0, (float)mapWidth, (float)screenHeight };
    if (CheckCollisionPointRec(GetMousePosition(), mapDrawingArea)) {
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < columns; y++) {
                if (CheckCollisionPointRec(mouseWorld, mapRects[x][y])) {
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                        setTile(x, y, selectedTileID);
                        Tile t = getTile(selectedTileID);
                       
                    }
                    else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
                        setTile(x, y, 0);
                    }
                }
            }
        }

        if (wheel != 0) {
    // cameraEditor.target = GetMousePosition();
            camera.zoom += wheel * 0.1f;
            if (camera.zoom < 0.2f) camera.zoom = 0.2f;
            if (camera.zoom > 2.0f) camera.zoom = 2.0f;
        }
         if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f / camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
    }


    }
   

    backButton->update();
   // expandAreaButton->update();
    //Editor TILE_SIZE handling
    //if (expandAreaButton->IsMouseDown()) {
    //    Vector2 mouseDel = GetMouseDelta();
    //    mapWidth += mouseDel.x;
    //    expandAreaButton->updatePos({(float) mapWidth - 20, screenHeight / 2 - 35 });
    //    //cout << 1;
    //}

    //File saving
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S))
        saveToFile("map1.txt");

    if (IsKeyDown(KEY_LEFT_CONTROL ) && IsKeyPressed(KEY_L))
        loadFromFile("map1.txt");
    //Back to menu
    if (backButton->IsClicked()) {
       Game::getInstance()->changeState(new MenuState());
    }

    //CameraEditor update
    // dt = GetFrameTime();
    //float speed = 200;
   
    Rectangle workplace = {mapWidth, 0, screenWidth, screenHeight};
    if (CheckCollisionPointRec(mousePos, workplace)) {
        if (wheel != 0) {
            // cameraEditor.target = GetMousePosition();
            cameraEditor.zoom += wheel * 0.1f;
            if (cameraEditor.zoom < 0.2f) cameraEditor.zoom = 0.2f;
            if (cameraEditor.zoom > 5.0f) cameraEditor.zoom = 5.0f;
        }

    
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        
                Vector2 delta = GetMouseDelta();
                delta = Vector2Scale(delta, -1.0f / cameraEditor.zoom);
                cameraEditor.target = Vector2Add(cameraEditor.target, delta);
                
        }
     }

        if (camera.target.x < 0) {
        camera.target.x = 0;
    }
    else if(camera.target.x > TILE_SIZE * columns){
        camera.target.x = TILE_SIZE * columns;
    }
}