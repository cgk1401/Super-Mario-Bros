#ifndef GLOBAL_H
#define GLOBAL_H
#include <raylib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

#include "../headers/Button.h"
using namespace std;


const int screenWidth = 1024;
const int screenHeight = 768;
Texture2D resizedImage(const char* imagePath, float width, float height);


#endif 