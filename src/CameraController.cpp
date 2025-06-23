// CameraController.cpp
#include "../headers/CameraController.h"
#include "cmath"
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
    
}
