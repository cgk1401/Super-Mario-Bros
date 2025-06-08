#include "../headers/Button.h"
#include "../headers/Global.h"
#include <iostream>
//CONSTRUCTORS & DESTRUCTOR
Button::Button() {
        bounds = {0,0,0,0};
        label = "";
        color = WHITE;
        hoverColor = WHITE;
        textColor = WHITE;
        useTexture = false;
        isHovered = false;
}
Button::~Button(){
    UnloadTexture(texture);
    UnloadTexture(textureOver);
}
Button::Button(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color hoverCol, Color textCol) {
        bounds = {x, y, width, height};
        label = labelText;
        color = buttonColor;
        this->hoverColor = hoverCol;
        textColor = textCol;
        useTexture = false;
        isHovered = false;
}
Button::Button(const char* imagePath, const char* imageOverPath, float x, float y, float width, float height){
        bounds = {x, y, width, height};
        label = "";
        color = RAYWHITE;
        hoverColor = RAYWHITE;
        textColor = RAYWHITE;
        isHovered = false;

        useTexture = true;
        texture = resizedImage(imagePath, width, height);
        textureOver = resizedImage(imageOverPath, width, height);
}

//METHODS
void Button::update(){
     Vector2 mousePoint = GetMousePosition();
    isHovered = CheckCollisionPointRec(mousePoint, bounds);
}

void Button::draw() {
    if(useTexture == false){
        DrawRectangleRec(bounds, isHovered ? hoverColor : color);
        int textWidth = MeasureText(label, 20);
        DrawTextEx(GetFontDefault(), label, {bounds.x + (bounds.width - textWidth) / 2, bounds.y + (bounds.height - 20) / 2}, 20, 3, textColor );
    }
    else{
         DrawTexture(!isHovered ? texture : textureOver, bounds.x, bounds.y, WHITE);
    }
}

Rectangle Button::getBound(){
    return bounds;
}

bool Button::IsClicked() {
    return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}