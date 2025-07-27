#pragma once
#include "raylib.h"
#include "../headers/Mario.h"
#include "../headers/Global.h"
#include <vector>
#include <string>
using namespace std;

struct ParallaxLayer {
    Texture2D texture;
    Rectangle srcRect;
    Rectangle pic1, pic2;
    float scrollX = 0;
    float scrollSpeed = 0.5;
    float scale = 1;
    float scaledWidth;

    ParallaxLayer() = default;
    ParallaxLayer(Texture2D tex, Rectangle srcRect, float speed, float s = 1)
        : texture(tex), srcRect(srcRect), scrollSpeed(speed), scale(s) {
        pic1 = { 0, 0, screenWidth, screenHeight };
        pic2 = { screenWidth, 0, screenWidth, screenHeight };
    }
};

class ParallaxManager {
private:
    vector<ParallaxLayer> layers;
    float screenHeight;

public:
    void addLayer(const char* filepath, Rectangle srcRect, float speed, float scale = 1);
    void update(Vector2 marioPos, Camera2D& camera, float deltatime);
    void draw();
    void unload();
};
