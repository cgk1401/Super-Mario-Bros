#include "../headers/ParallaxManager.h"
#include "../headers/Global.h"
#include "../headers/Map.h"
#include <cmath>
#include <iostream>
void ParallaxManager::addLayer(const char* filepath, Rectangle srcRect, float speed, float scale) {
    Texture2D tex = LoadTexture(filepath);
    ParallaxLayer layer(tex, srcRect, speed, scale);
    layer.scaledWidth = srcRect.width * scale;

    layers.push_back(layer);
}

void ParallaxManager::update(Vector2 marioPos, Camera2D& camera, float deltaTime) {
    for (auto& layer : layers) {
        // offset parallax dựa trên tốc độ
        float offset = fmod(camera.target.x * layer.scrollSpeed, layer.scaledWidth);

        if (offset < 0) offset += layer.scaledWidth;

        layer.scrollX = offset;
    }
}


void ParallaxManager::draw() {
    for (auto& layer : layers) {
        // vẽ tile đầu
        DrawTexturePro(layer.texture, layer.srcRect,
            { -layer.scrollX, 0, layer.scaledWidth, layer.srcRect.height * layer.scale },
            { 0, 0 }, 0, WHITE);

        // vẽ tile thứ 2 liền kề
        DrawTexturePro(layer.texture, layer.srcRect,
            { -layer.scrollX + layer.scaledWidth, 0, layer.scaledWidth, layer.srcRect.height * layer.scale },
            { 0, 0 }, 0, WHITE);
    }
}


void ParallaxManager::unload() {
    for (auto& layer : layers) {
        UnloadTexture(layer.texture);
    }
    layers.clear();
}