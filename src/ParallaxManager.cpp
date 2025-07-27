#include "../headers/ParallaxManager.h"
#include "../headers/Global.h"
#include "../headers/Map.h"
#include <cmath>
#include <iostream>
void ParallaxManager::addLayer(const char* filepath, Rectangle srcRect, float speed, float scale) {
    Texture2D tex = LoadTexture(filepath);
    ParallaxLayer layer;
    layer.texture = tex;
    layer.srcRect = srcRect;
    layer.scrollSpeed = speed; 
    layer.scale = scale;
    layer.scrollX = 0.0;

    layer.scaledWidth = srcRect.width * scale;

    layers.push_back(layer);
}

void ParallaxManager::update(Vector2 marioPos, Camera2D& camera, float deltaTime) {
    Vector2 screenPos = GetWorldToScreen2D(marioPos, camera);


    
       for (auto& layer : layers) {
           layer.scrollX = -camera.target.x * layer.scrollSpeed * 0.8;

           if (layer.scrollX >= layer.scaledWidth) {
               layer.scrollX -= layer.scaledWidth;
           }
           else if (layer.scrollX < 0.0f) {
               layer.scrollX += layer.scaledWidth;
           }
       }
   
}

void ParallaxManager::draw() {
    float screenWidth = (float)GetScreenWidth();
    for (const auto& layer : layers) {
        //int numRepeats = (int)ceil((screenWidth + layer.scaledWidth) / layer.scaledWidth);

        for (int i = -1; i <  20; i++) {
            Rectangle destRect = {
                layer.scrollX + i * layer.scaledWidth, 
                0.0f,                                 
                layer.scaledWidth,                    
                layer.srcRect.height * layer.scale   
            };
            DrawTexturePro(layer.texture, layer.srcRect, destRect, { 0.0f, 0.0f }, 0.0f, WHITE);
        }
    }
}

void ParallaxManager::unload() {
    for (auto& layer : layers) {
        UnloadTexture(layer.texture);
    }
    layers.clear();
}