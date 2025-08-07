#include "../headers/Global.h"
#include "../headers/Map.h"
Map* Global::map = nullptr;
Camera2D Global::camera = {};
pair<int,int> Global::level = {1,1};
Character* Global::character = nullptr;

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

inline int operator+(int lhs, MapTheme rhs) {
    return lhs + static_cast<int>(rhs);
}

float approach(float current, float target, float increase) {
	if (current < target) {
		return fmin(current + increase, target);
	}
	return fmax(current - increase, target);
}

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}
