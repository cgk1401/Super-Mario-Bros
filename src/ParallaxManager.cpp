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
    layer.scrollSpeed = speed; // Tốc độ cuộn, giá trị dương để cuộn sang trái
    layer.scale = scale;
    layer.scrollX = 0.0f;

    // Tính toán chiều rộng texture sau khi scale
    layer.scaledWidth = srcRect.width * scale;

    layers.push_back(layer);
}

void ParallaxManager::update(Mario& mario, Camera2D& camera, float deltaTime) {
    Vector2 marioPos = mario.getPos();
    Vector2 screenPos = GetWorldToScreen2D(marioPos, camera);


    
        for (auto& layer : layers) {
            // Cập nhật vị trí cuộn dựa trên tốc độ và deltaTime
            layer.scrollX = -camera.target.x * layer.scrollSpeed / layer.scale;

            // Đảm bảo scrollX nằm trong khoảng [-scaledWidth, 0] để lặp vô hạn
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
        // Tính số lần texture cần vẽ để lấp đầy màn hình
        int numRepeats = (int)ceil((screenWidth + layer.scaledWidth) / layer.scaledWidth);

        // Vẽ nhiều texture để tạo hiệu ứng lặp vô hạn
        for (int i = -1; i <  20; i++) {
            Rectangle destRect = {
                layer.scrollX + i * layer.scaledWidth, // Vị trí X
                0.0f,                                 // Vị trí Y
                layer.scaledWidth,                    // Chiều rộng
                layer.srcRect.height * layer.scale    // Chiều cao
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