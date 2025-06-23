#pragma once
#include "raylib.h"

class CameraController {
private:
    Camera2D camera;

public:
    void init(Vector2 startPos);
    void update(Rectangle playerBound, float screenWidth);
    Camera2D& getCamera() { return camera; }
};