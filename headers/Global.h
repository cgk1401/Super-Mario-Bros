#ifndef GLOBAL_H
#define GLOBAL_H
#include <raylib.h>
#include "../headers/Button.h"
#include "../headers/Map.h"

const int screenWidth = 1024;
const int screenHeight = 768;
Texture2D resizedImage(const char* imagePath, float width, float height);

#endif 