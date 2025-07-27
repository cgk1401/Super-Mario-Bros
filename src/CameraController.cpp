// CameraController.cpp
#include "../headers/CameraController.h"
#include "../headers/Global.h"
#include "cmath"
#include <raymath.h>
void CameraController::init(Vector2 startPos) {
    camera = { 0 };
    camera.target = startPos;
    camera.offset = { 0, -32 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}
void CameraController::update(Rectangle playerBound, float endPos) {
    float threshold = screenWidth / 2.0f;
    float desiredCamX = camera.target.x;
    float playerWidth = abs(playerBound.width);
    // if (playerBound.x + playerBound.width > camera.target.x + threshold) {
    //     desiredCamX = playerBound.x + playerBound.width - threshold;
    // }
    // else if (playerBound.x < camera.target.x - threshold) {
    //     desiredCamX = playerBound.x - threshold;
    // }

    // float maxCamX = endPos - screenWidth; 
    // if (desiredCamX > maxCamX) desiredCamX = maxCamX;

    // if (desiredCamX < 0) desiredCamX = 0;

    // camera.target.x = desiredCamX;


   

    //camera follows mario in whole game (TEST!!)
    
    if (playerBound.x + playerWidth / 2 - screenWidth / 2 > 0)
        camera.target.x = playerBound.x + playerWidth / 2 - screenWidth / 2 ;
    else camera.target.x = 0;
    camera.target.y = 0;

    // float wheel = GetMouseWheelMove();
    
    // if (wheel != 0) {
    //     // cameraEditor.target = GetMousePosition();
    //     camera.zoom += wheel * 0.1f;
    //     if (camera.zoom < 0.2f) camera.zoom = 0.2f;
    //     if (camera.zoom > 5.0f) camera.zoom = 5.0f;
    // }
    // if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {

    //     Vector2 delta = GetMouseDelta();
    //     delta = Vector2Scale(delta, -1.0f / camera.zoom);
    //     camera.target = Vector2Add(camera.target, delta);

    // }
    
}
