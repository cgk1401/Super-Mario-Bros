#include "../headers/MapEditor.h"
#include <iostream>
#include <fstream>
#include "../headers/Game.h"
#include "../headers/MenuState.h"
#include "../headers/TileBehavior.h"
#include "../headers/Global.h"
#include "raymath.h"
using namespace std;

MapEditor::MapEditor(const char* path, int r, int c) : Map(path, r, c) {
    camera.offset = { 0, screenHeight * 0.1f };
    camera.target = { 0, 0 };
    camera.rotation = 0;
    camera.zoom = 0.9;

    cameraEditor.offset = {0,0 };
    cameraEditor.target = { (float) mapWidth, 0 };
    cameraEditor.rotation = 0;
    cameraEditor.zoom = 1.0;

    mapWidth = screenWidth * 0.7f;
    uiWidth = screenWidth - (int)mapWidth;

    back_button = new Button(Singleton<TextureManager>::getInstance().load(TextureType::BUTTON), 10, 10 , screenWidth / 3 * 0.5f, screenHeight * 0.15f * 0.5f, "HOME", WHITE);

    tilePicking_button = new Button("../assets/GUI/mapeditor_tile_picking_tool.png", screenWidth * 0.63f, 10.0, screenHeight * 0.15f * 0.5f, screenHeight * 0.15f * 0.5f, "", WHITE, 0, "Paint");
    eraserTool_button = new Button("../assets/GUI/mapeditor_eraser_tool.png", screenWidth * 0.57, 10, screenHeight * 0.15f * 0.5f, screenHeight * 0.15f * 0.5f, "", WHITE, 0, "Eraser Tool");
    save_button = new Button("../assets/GUI/mapeditor_save_button.png",  screenWidth * 0.19f, 14, screenHeight * 0.14f * 0.5f, screenHeight * 0.14f * 0.5f, "", WHITE, 0, "Save to file");
    editType = EditorMode::DRAW;

    const int amount_button = 2;
    ButtonLayoutConfig cfg(amount_button);
    const char* buttonLabels[amount_button] = {"LOAD", "QUIT" };

    option_buttons = CreateButtons(buttonLabels, cfg);


    world_1_1_test = LoadTexture("../assets/Map/World 1-1.png");
}


void MapEditor::saveToFile(const char* filename) {
    ofstream MyFile(filename);

    if (!MyFile.is_open()) {
        cerr << "Error: Could not open file for saving: " << filename << endl;
        return;
    }
    
  
    int limitCol = columns;
   
    for (int y = columns - 1; y >= 0; y--) {
        for (int x = 0; x < rows; x++) {
            if (mapData[x][y].tileID != 0) {
                limitCol = y;
                goto found;
            }
        }
    }
    found:

    MyFile << rows << " " << limitCol << "\n";
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < limitCol; y++) {
            // Save TileID directly
            MyFile << mapData[x][y].tileID; // Access tileID from MapTileInstance
            if (y < columns - 1) MyFile << " ";
        }
        MyFile << endl;
    }

    cout << "Saved file successfully: " << filename << endl;
    MyFile.close();
}

void MapEditor::handleInput() {
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
    Vector2 mousePos = GetMousePosition();
    Rectangle workplace = {mapWidth, 0, screenWidth, screenHeight};
    for (int r = 0; r < tileRows; r++) {
        for (int c = 0; c < tileSetSourceRects[r].size(); c++) {
            Rectangle tileSrc = tileSetSourceRects[r][c];
            Rectangle tileDest = { (float)uiStartX + 10 + (float)c * TILE_SIZE, (float)currentY + (float)r * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE };

            if (CheckCollisionPointRec(mousePos, workplace) && CheckCollisionPointRec(mouseWorldPos, tileDest) ) {
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
            }

        }
    }
}

void MapEditor::render() {
   
    //Tile map
    Rectangle mapDrawingArea = { 0, 0, (float)mapWidth, (float)screenHeight };
    DrawText("Selected:", 20, screenHeight * 0.2f - 60, 20, BLACK);
    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
    DrawRectangle(0, 0, mapWidth, camera.offset.y, DARKBLUE);

    BeginScissorMode(0, camera.offset.y - 1, screenWidth * 0.75f, screenHeight - camera.offset.y + 1);
    BeginMode2D(camera);
     DrawTexturePro(world_1_1_test,
                   { 0,0, (float) world_1_1_test.width, (float) world_1_1_test.height},
                   {0 * Map::TILE_SIZE, -2 * Map::TILE_SIZE,  (float) world_1_1_test.width * 4, (float) world_1_1_test.height * 4},
                   {0,0}, 0,
                   Fade(WHITE, 0.4f));
    Map::draw(true); // Draw map with grid lines
    EndMode2D();

    if(editType == EditorMode::DRAW)
        for (int x = 0; x < brushBuffer.size(); x++) {
            for (int y = 0; y < brushBuffer[x].size(); y++) {
                DrawTexturePro(texture, brushBuffer[x][y], { (float)10 + 110 + x * 40, (float)screenHeight * 0.2f - 60 + y * 40, 40, 40 }, { 0,0 }, 0, WHITE);

                if (CheckCollisionPointRec(GetMousePosition(), mapDrawingArea)) {
                    BeginMode2D(camera);
                    Vector2 mouseOnTilePos = { (int)mouseWorld.x / TILE_SIZE,(int)mouseWorld.y / TILE_SIZE };
                    Rectangle dest = { (mouseOnTilePos.x + x) * TILE_SIZE, (mouseOnTilePos.y + y) * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                    DrawTexturePro(texture, brushBuffer[x][y], dest, { 0,0 }, 0, Fade(WHITE, 0.5f));
                    EndMode2D();
                }
            }
        }
    EndScissorMode();

    
    int uiStartX = mapWidth;

    DrawRectangle(uiStartX, 0, uiWidth, screenHeight, LIGHTGRAY);
    DrawText("Tileset:", uiStartX + 10, 10, 20, BLACK);

    int currentY = 40; 

    Vector2 mouseEditorWorld = GetScreenToWorld2D(GetMousePosition(), cameraEditor);
    BeginScissorMode(uiStartX + 10, currentY,screenWidth - uiStartX - 10, screenHeight - currentY);
    
    BeginMode2D(cameraEditor);
    for (int r = 0; r < tileRows; r++) {
        for (int c = 0; c < tileSetSourceRects[r].size(); c++) {
            Rectangle tileSrc = tileSetSourceRects[r][c];
            Rectangle tileDest = { (float)uiStartX + 10 + (float)c * (TILE_SIZE), (float)currentY + (float)r * (TILE_SIZE), (float)TILE_SIZE, (float)TILE_SIZE };
            
            DrawTexturePro(texture, tileSrc, tileDest, { 0,0 }, 0, CheckCollisionPointRec(mouseEditorWorld, tileDest) ? Fade(WHITE, 0.8f):WHITE);
            
        }
    }
    EndMode2D();
    
    // Draw currently selected tile info
    uiStartX = 10;

    //DRAW RECT LINE
    BeginMode2D(cameraEditor);
    if (dragStartTile.x >= 0 && dragStartTile.y >= 0 &&
        dragEndTile.x >= 0 && dragEndTile.y >= 0) {

        int minX = min(dragStartTile.y, dragEndTile.y);
        int minY = min(dragStartTile.x, dragEndTile.x);
        int maxX = max(dragStartTile.y, dragEndTile.y);
        int maxY = max(dragStartTile.x, dragEndTile.x);

        Color c = isDragging ? GREEN : RED; 
        if(isDragging){
            DrawRectangle((float)mapWidth + 10 + minX * TILE_SIZE,
                                (float)currentY + minY * TILE_SIZE,
                                (float) (maxX - minX + 1) * TILE_SIZE,
                                (float)(maxY - minY + 1) * TILE_SIZE, Fade(WHITE, 0.4f));
        }
        DrawRectangleLines((float)mapWidth + 10 + minX * TILE_SIZE,
                                (float)currentY + minY * TILE_SIZE,
                                (float) (maxX - minX + 1) * TILE_SIZE,
                                (float)(maxY - minY + 1) * TILE_SIZE, c);
    }
    EndMode2D();
    EndScissorMode();

    tilePicking_button->draw();
    eraserTool_button->draw();
    save_button->draw();
    if (editType == EditorMode::DRAW) {
        DrawRectangleLinesEx(tilePicking_button->getBounds(), 1, YELLOW);
    }
    else if (editType == EditorMode::ERASE) {
        DrawRectangleLinesEx(eraserTool_button->getBounds(), 1, YELLOW);
    }


    if (_option_buttons) {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.6f));
        for (auto& button : option_buttons) {
            button->draw();
        }
    }
    back_button->draw();
    if (saveFileNoti_timer.isRunning()) {
        const float rectW = screenWidth * 0.6;
        const float rectH = 60;
        float startX = screenWidth / 2 - rectW / 2;
        float startY = screenHeight / 2 - rectH / 2;
        DrawRectangle(startX, startY, rectW, rectH, BLACK);
        DrawText("SAVED FILE SUCCESSFULLY", startX + 50, startY + 10, 40, WHITE);
    }
    save.render();
} 

void MapEditor::update(float deltatime) {
    back_button->update(deltatime);
    if (back_button->IsClicked()) _option_buttons = !_option_buttons;
    if (_option_buttons) {
        for (auto& button : option_buttons) {
            button->update(deltatime);
        }


         if (option_buttons[0]->IsClicked()) { //LOAD
            loadFromFile("map1.txt", true);
            _option_buttons = false;
        }
        else if (option_buttons[1]->IsClicked()) {
            Singleton<Game>::getInstance().changeState(new MenuState());
        }
        return;
    }


    Map::update(true); // Update camera movement
    handleInput();
    saveFileNoti_timer.update(deltatime);
    tilePicking_button->update(deltatime);
    eraserTool_button->update(deltatime);
    save_button->update(deltatime);

    if (tilePicking_button->IsClicked()) {
        editType = EditorMode::DRAW;
    }
    else if (eraserTool_button->IsClicked()) {
        editType = EditorMode::ERASE;
    }
    else if(save_button->IsClicked()){
        saveToFile("map1.txt");
        saveFileNoti_timer.start(1);
        _option_buttons = false;
        
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
                    if (editType == EditorMode::DRAW) {
                        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                            Vector2 mouseOnTilePos = { (int)mouseWorld.x / TILE_SIZE,(int)mouseWorld.y / TILE_SIZE };
                            Rectangle pickedTile = { mouseOnTilePos.x * TILE_SIZE , mouseOnTilePos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                            for (int i = 0; i < brushBuffer.size(); i++) {
                                for (int j = 0; j < brushBuffer[i].size(); j++) {
                                    int coor_x = brushBuffer[i][j].y / TILE_SIZE; //tileSetSrc
                                    int coor_y = brushBuffer[i][j].x / TILE_SIZE;
                                    int tileID = getTileIDFromCoords(coor_x + 1, coor_y + 1);
                                    int pasteY = (pickedTile.x + i * TILE_SIZE) / TILE_SIZE;
                                    int pasteX = (pickedTile.y + j * TILE_SIZE) / TILE_SIZE;

                                    if (IsInsideMap(pasteX, pasteY)) {
                                        setTile(pasteX, pasteY, tileID);
                                    }
                                }
                            }
                        }
                    }
                    else if (editType == EditorMode::ERASE) {
                         if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                            removeTile(x, y);
                        }
                    }
                }
            }     
        }
            
     }

    if (CheckCollisionPointRec(mousePos, mapDrawingArea)) {
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

   

    //CameraEditor update

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

        /*if (camera.target.x < 0) {
        camera.target.x = 0;
    }
    else if(camera.target.x > TILE_SIZE * columns){
        camera.target.x = TILE_SIZE * columns;
    }*/

    save.update(deltatime);
}

bool MapEditor::IsInsideMap(int row, int col){
    return row < rows && col < columns && row >= 0 && col >= 0;
}

