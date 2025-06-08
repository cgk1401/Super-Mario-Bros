#ifndef BUTTON_H
#define BUTTON_H
#include <raylib.h>


class Button {
private:
    Rectangle bounds;
    const char* label;
    Color color;
    Color hoverColor;
    Color textColor;
    bool isHovered; 

    Texture2D texture;
    Texture2D textureOver;
    bool useTexture;
public:
    Button();
    Button(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color hoverCol, Color textCol);
    Button(const char* imagePath, const char* imageOverPath, float x, float y, float width, float height);                         //Button from image
    ~Button();
    
    Rectangle getBound();
    bool IsClicked();

    void update();
    void draw();
};


#endif