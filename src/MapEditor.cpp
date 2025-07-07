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

void MapEditor::handleInput(Game& game) {
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

    //MULTI-TILE brush
    int uiStartX = mapWidth;
     int currentY = 40; 
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cameraEditor);
    Rectangle workplace = {mapWidth, 0, screenWidth, screenHeight};
    for (int r = 0; r < tileRows; r++) {
        for (int c = 0; c < tileSetSourceRects[r].size(); c++) {
            Rectangle tileSrc = tileSetSourceRects[r][c];
            Rectangle tileDest = { (float)uiStartX + 10 + (float)c * TILE_SIZE, (float)currentY + (float)r * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE };

           // int currentTileID = getTileIDFromCoords(r + 1, c + 1);

            if (CheckCollisionPointRec(mouseWorldPos, tileDest) ) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    isDragging = true;
                    dragStartTile = { (float) r, (float)c };
                    dragEndTile = dragStartTile;
                }
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    dragEndTile = { (float) r, (float) c };
                }
                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                    isDragging = false;
                    
                    // Tạo buffer vùng copy
                    int minX = min(dragStartTile.x, dragEndTile.x);
                    int minY = min(dragStartTile.y, dragEndTile.y);
                    int maxX = max(dragStartTile.x, dragEndTile.x);
                    int maxY = max(dragStartTile.y, dragEndTile.y);

                    brushBuffer.clear();
                    for (int y = minY; y <= maxY; y++) {
                        vector<Rectangle> row;
                        for (int x = minX; x <= maxX; x++) {
                            row.push_back(tileSetSourceRects[x][y]); // copy tile
                        }
                        brushBuffer.push_back(row);
                    }
                }
               // cout << "Selected Tile ID: " << selectedTileID << " (Tileset coords: " << r + 1 << "," << c + 1 << ")\n";
            }

        }
    }
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
            Rectangle tileDest = { (float)uiStartX + 10 + (float)c * (TILE_SIZE), (float)currentY + (float)r * (TILE_SIZE), (float)TILE_SIZE, (float)TILE_SIZE };

            DrawTexturePro(texture, tileSrc, tileDest, { 0,0 }, 0, WHITE);
        }
    }
    EndMode2D();
    // Draw currently selected tile info
    uiStartX = 10;
    Rectangle mapDrawingArea = { 0, 0, (float)mapWidth, (float)screenHeight };
    DrawText("Selected:", uiStartX + 10, screenHeight * 0.2f - 60, 20, BLACK);
    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);

      for(int x = 0; x < brushBuffer.size(); x++){
        for(int y = 0; y < brushBuffer[x].size(); y++){
            // cout << "(" <<  brushBuffer[x][y].x / TILE_SIZE;
            // cout << ", " << brushBuffer[x][y].y / TILE_SIZE << ")" <<  endl;
                //cout <<"render: " << endl;
                
                DrawTexturePro(texture,  brushBuffer[x][y], { (float)uiStartX + 110 + x * 40, (float)screenHeight * 0.2f - 60 + y * 40, 40, 40 }, { 0,0 }, 0, WHITE);

                if (CheckCollisionPointRec(GetMousePosition(), mapDrawingArea)) {
                    BeginMode2D(camera);
                    Vector2 mouseOnTilePos = { (int)mouseWorld.x / TILE_SIZE,(int)mouseWorld.y / TILE_SIZE };
                    Rectangle dest = { (mouseOnTilePos.x + x) * TILE_SIZE, (mouseOnTilePos.y  + y) * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                    DrawTexturePro(texture,  brushBuffer[x][y], dest, { 0,0 }, 0, WHITE);

                    DrawRectangleRec(dest, Fade(BLUE, 0.3));
                    //DrawRectangleLinesEx(dest, 0.4, BLUE);
                    EndMode2D();
                }
            }
        }

    //DRAW RECT LINE
    BeginMode2D(cameraEditor);
    if (dragStartTile.x >= 0 && dragStartTile.y >= 0 &&
        dragEndTile.x >= 0 && dragEndTile.y >= 0) {

        int minX = min(dragStartTile.y, dragEndTile.y);
        int minY = min(dragStartTile.x, dragEndTile.x);
        int maxX = max(dragStartTile.y, dragEndTile.y);
        int maxY = max(dragStartTile.x, dragEndTile.x);

        Color c = isDragging ? GREEN : RED; 

        // DrawRectangleLinesEx({(float)mapWidth + 10 + minX * TILE_SIZE,
        //                         (float)currentY + minY * TILE_SIZE,
        //                         (float) (maxX - minX + 1) * TILE_SIZE,
        //                         (float)(maxY - minY + 1) * TILE_SIZE}, 0.2, c);
        DrawRectangleLines((float)mapWidth + 10 + minX * TILE_SIZE,
                                (float)currentY + minY * TILE_SIZE,
                                (float) (maxX - minX + 1) * TILE_SIZE,
                                (float)(maxY - minY + 1) * TILE_SIZE, c);
    }
    EndMode2D();

    backButton->draw();
    //expandAreaButton->draw();
}

void MapEditor::update(Game& game) {
    Map::update(true); // Update camera movement
    handleInput(game);
 
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
                        Vector2 mouseOnTilePos = { (int)mouseWorld.x / TILE_SIZE,(int)mouseWorld.y / TILE_SIZE };
                        Rectangle pickedTile = { mouseOnTilePos.x * TILE_SIZE , mouseOnTilePos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                        for (int i = 0; i < brushBuffer.size(); i++) {
                            for (int  j= 0; j < brushBuffer[i].size(); j++) {
                                int coor_x = brushBuffer[i][j].y / TILE_SIZE; //tileSetSrc
                                int coor_y = brushBuffer[i][j].x / TILE_SIZE;
                                //cout << "update: " << endl;
                                int tileID = getTileIDFromCoords(coor_x + 1, coor_y  + 1);
                                //cout << "ID: " << tileID << endl;
                                int pasteY = (pickedTile.x + i * TILE_SIZE) / TILE_SIZE;
                                int pasteX = (pickedTile.y + j * TILE_SIZE) / TILE_SIZE;
                                
                                if (IsInsideMap(pasteX, pasteY)) {
                                    setTile(pasteX, pasteY , tileID);
                                }
                            }
                        }
                        }
                    else if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
                            removeTile(x, y);
                    }
                }
            }     
        }
            
     }

        if (wheel != 0) {
    // cameraEditor.target = GetMousePosition();
            camera.zoom += wheel * 0.1f;
            if (camera.zoom < 0.7f) camera.zoom = 0.7f;
            if (camera.zoom > 1.0f) camera.zoom = 1.0f;
        }
        /* if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f / camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
    }*/


    
   

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

bool MapEditor::IsInsideMap(int row, int col){
    return row < rows && col < columns && row >= 0 && col >= 0;
}

