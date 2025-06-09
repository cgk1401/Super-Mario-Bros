#include "../headers/Button.h"
#include "../headers/Global.h"
#include <iostream>

Button::Button() {
    bounds = { 0, 0, 0, 0 };
    label = "";
    color = WHITE;
    hoverColor = GRAY;
    textColor = BLACK;
    isHovered = false;
    fontSize = 20;
    useTexture = false;
}

Button::Button(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color hoverCol, Color textCol, int fontSize) {
    bounds = { x, y, width, height };
    label = labelText;
    color = buttonColor;
    hoverColor = hoverCol;
    textColor = textCol;
    this->fontSize = fontSize;
    isHovered = false;
    useTexture = false; 
}

Button::Button(const char* imagePath, float x, float y, float width, float height, const char* labelText, Color textCol, int fontSize) {
    bounds = { x, y, width, height };
    label = labelText;
    textColor = textCol;
    this->fontSize = fontSize;
    isHovered = false;
    useTexture = true;

    texture = resizedImage(imagePath, width, height);
}

Button::~Button() {
    //Ơ sao bị lỗi Unload liên tục => ko draw dc texture nè.
    if (useTexture && texture.id != 0) {
        TraceLog(LOG_INFO, "Unloading texture: %s", label.c_str());
        UnloadTexture(texture);
    }
}
void Button::operator=(const Button& b) {
    bounds = b.bounds;
    label = b.label;
    color = b.color;
    hoverColor = b.hoverColor;
    textColor = b.textColor;
    isHovered = b.isHovered;
    fontSize = b.fontSize;
    useTexture = b.useTexture;

    texture = b.texture;
   
}
void Button::update() {
    Vector2 mouse = GetMousePosition();
    isHovered = CheckCollisionPointRec(mouse, bounds);
    
}

void Button::draw() {

    if (useTexture) {
        float scaleX = bounds.width / texture.width;
        float scaleY = bounds.height / texture.height;
       /* DrawTextureEx(texture, { bounds.x, bounds.y }, 0.0f, scaleX, WHITE);*/
        DrawTexture(texture, bounds.x, bounds.y, WHITE);
    }
    else {
        DrawRectangleRec(bounds, isHovered ? hoverColor : color);
    }

    int textWidth = MeasureText(label.c_str(), fontSize);
    float textX = bounds.x + (bounds.width - textWidth) / 2;
    float textY = bounds.y + (bounds.height - fontSize) / 2;
    DrawText(label.c_str(), (int)textX, (int)textY, fontSize, textColor);
}

bool Button::IsClicked() {
    return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

Rectangle Button::getBounds() const {
    return bounds;
}
