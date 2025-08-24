#pragma once
#include "raylib.h"

class CameraController {
public:
    void init(Vector2 startPos);
    void update(Rectangle playerBound, float screenWidth);
    Camera2D& getCamera() { return camera; }
private:
    Camera2D camera;

};