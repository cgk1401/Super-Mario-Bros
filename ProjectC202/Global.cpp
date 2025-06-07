#include "Global.h"

Texture2D resizedImage(const char* imagePath, float width, float height){
    Image img = LoadImage(imagePath);
    ImageResize(&img, (int)width, (int)height);  
    Texture2D texture = LoadTextureFromImage(img);
    UnloadImage(img);  
    return texture;  
}