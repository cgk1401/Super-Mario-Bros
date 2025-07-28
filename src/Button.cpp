#include "../headers/Button.h"
#include "../headers/Global.h"
#include <iostream>

#define MULTI_SCALE 1.1f
#define PRESS_SCALE 0.8f

Button::Button() {
    bounds = { 0, 0, 0, 0 };
    label = "";
    color = WHITE;
    hoverColor = GRAY;
    textColor = BLACK;
    isHovered = false;
    fontSize = 20;
    useTexture = false;
    Tooltip = "";

    FONT = GetFontDefault();
}

Button::Button(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color hoverCol, Color textCol, int fontSize, const char* tooltip) {
    bounds = { x, y, width, height };
    label = labelText;
    color = buttonColor;
    hoverColor = hoverCol;
    textColor = textCol;
    this->fontSize = fontSize;
    isHovered = false;
    useTexture = false; 
    Tooltip = tooltip;
    FONT = LoadFont("../assets/font/PolygonParty.ttf");
}

Button::Button(const char* imagePath, float x, float y, float width, float height, const char* labelText, Color textCol, int fontSize, const char* tooltip) {
    bounds = { x, y, width, height };
    label = labelText;
    textColor = textCol;
    this->fontSize = fontSize;
    isHovered = false;
    useTexture = true;

    Tooltip = tooltip;
    texture = LoadTexture(imagePath);
    FONT = LoadFont("../assets/font/PolygonParty.ttf");

}
Button::Button(const Texture2D& texture, float x, float y, float width, float height, const char* labelText, Color textCol, int fontSize, const char* tooltip){
    bounds = { x, y, width, height };
    label = labelText;
    textColor = textCol;
    this->fontSize = fontSize;
    isHovered = false;
    useTexture = true;

    Tooltip = tooltip;
    this->texture = texture;
    FONT = LoadFont("../assets/font/PolygonParty.ttf");

}

Button::~Button() {
    //Ơ sao bị lỗi Unload liên tục => ko draw dc texture nè.
    // if (useTexture && texture.id != 0) {
    //     TraceLog(LOG_INFO, "Unloading texture: %s", label.c_str());
    //     UnloadTexture(texture);
    // }
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

void Button::update(float deltatime) {
    Vector2 mouse = GetMousePosition();
    isHovered = CheckCollisionPointRec(mouse, bounds);
    
    if (isHovered) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isPressing = true;
            Singleton<SoundManager>::getInstance().play(SoundType::CLICK_BUTTON);
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && isPressing) {
            if(scale == PRESS_SCALE) {
                isPressing = false;
                goto go_here;
            }
            scale = approach(scale, PRESS_SCALE, deltatime / 2);
            
        }
        else if (isPressing) {
            isPressing = false;
            scale = approach(scale, MULTI_SCALE, deltatime / 2);
        }
        else {
            go_here:
            scale = approach(scale, MULTI_SCALE, deltatime / 2);
        }
    }
    else {
        scale = approach(scale, 1.0f, deltatime / 2 );
        isPressing = false;
    }

}


void Button::draw() {
    Rectangle dest;
    dest.width = bounds.width * scale;
    dest.height = bounds.height * scale;
    dest.x = bounds.x + (bounds.width - dest.width) / 2.0f;
    dest.y = bounds.y + (bounds.height - dest.height) / 2.0f;
    
    if (useTexture) {
        Rectangle src = {0, 0, (float)texture.width, (float)texture.height};
        Color drawColor = isHovered ? Color{180, 180, 180, 255} : WHITE;

        DrawTexturePro(texture, src, dest, {0, 0}, 0.0f, drawColor);
    } else {
        DrawRectangleRec(dest, isHovered ? hoverColor : color);
    }
    float textFontSize = fontSize * scale;
    float spacing = 2;
    Vector2 text = MeasureTextEx(FONT, label.c_str(), textFontSize, spacing);
    
    float textX = dest.x + (dest.width - text.x) / 2;
    float textY = dest.y + (dest.height - text.y) / 2;
    //DrawText(label.c_str(), (int)textX, (int)textY, textFontSize, textColor);
    DrawTextEx(FONT, label.c_str(), { textX, textY }, textFontSize, spacing, textColor);
    if (isHovered && Tooltip != "") {
        float textFontSize = 20;
        int textWidth = MeasureText(Tooltip.c_str(), textFontSize);
        Rectangle tooltipDest;
        tooltipDest.x = bounds.x + bounds.width / 2;
        tooltipDest.y = bounds.y + bounds.height + 1;
        tooltipDest.width = textWidth + 10;
        tooltipDest.height = 30;
        float textX = tooltipDest.x + 5;
        float textY = tooltipDest.y + 5;  
        DrawRectangleRec(tooltipDest, DARKGRAY);
        DrawText(Tooltip.c_str(), textX, textY, textFontSize, WHITE);
    }
}
void Button::updateScale(float newScale) {
    
    scale = newScale;
}


bool Button::IsClicked() {
    return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool Button::IsMouseDown() {
    return isHovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}

void Button::updatePos(Vector2 newPos) {
    this->bounds.x = newPos.x;
    this->bounds.y = newPos.y;
}
Rectangle Button::getBounds() const {
    return bounds;
}
