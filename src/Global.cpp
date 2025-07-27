#include "../headers/Global.h"

Map* Global::map = nullptr;
Camera2D Global::camera = {};
pair<int,int> Global::level = {1,1};

Texture2D resizedImage(const char* imagePath, float width, float height){
    Image img = LoadImage(imagePath);
    if (img.data == NULL) {
        TraceLog(LOG_ERROR, "Failed to load image: %s", imagePath);
        return Texture2D();
    }
    ImageResize(&img, (int)width, (int)height);  
    Texture2D texture = LoadTextureFromImage(img);
    if (texture.id <= 0) {
        TraceLog(LOG_ERROR, "Failed to load texture from image: %s", imagePath);
        UnloadImage(img);  
        return Texture2D(); 
    }
    UnloadImage(img); 
    TraceLog(LOG_INFO, "Successfully loaded file!");
    return texture;  
}

bool operator==(pair<int, int> a, pair<int,int>b){
    return a.first == b.first && a.second == b.second;
}