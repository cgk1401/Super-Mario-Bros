// CameraController.cpp
#include "../headers/CameraController.h"
#include "cmath"
#include <raymath.h>
void CameraController::init(Vector2 startPos) {
    camera = { 0 };
    camera.target = startPos;
    camera.offset = { 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void CameraController::update(Rectangle playerBound, float screenWidth) {
 
    float threshold = screenWidth / 2.0f;
    /* //cam follows mario when he exceeds threhold!! USE THIS!!!!
    if (playerBound.x  + playerBound.width > camera.target.x + threshold) {
        camera.target.x = playerBound.x + playerBound.width - threshold;
    }
    else if (playerBound.x < camera.target.x - threshold) {
        camera.target.x = playerBound.x + playerBound.width + threshold;
    }
   */

    //camera follows mario in whole game (TEST!!)
    float playerWidth = abs(playerBound.width);
    if (playerBound.x + playerWidth / 2 - screenWidth / 2 > 0)
        camera.target.x = playerBound.x + playerWidth / 2 - screenWidth / 2 ;
    else camera.target.x = 0;
    camera.target.y = 0;

    float wheel = GetMouseWheelMove();
    
    if (wheel != 0) {
        // cameraEditor.target = GetMousePosition();
        camera.zoom += wheel * 0.1f;
        if (camera.zoom < 0.2f) camera.zoom = 0.2f;
        if (camera.zoom > 5.0f) camera.zoom = 5.0f;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {

        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / camera.zoom);
        camera.target = Vector2Add(camera.target, delta);

    }
    
}
