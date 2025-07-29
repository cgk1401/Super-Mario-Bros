#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <string>
#include "../headers/Timer.h"

class Button {
private:
    Rectangle bounds;
    std::string label;
    Color color;
    Color hoverColor;
    Color textColor;
    bool isHovered;
    int fontSize;

    Texture2D texture;
    bool useTexture;
    float scale = 1;
    float defaultScale = 1;
    bool isPressing = false;
    std::string Tooltip;

    Font FONT;
public:
    Button();
    Button(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color hoverCol, Color textCol, int fontSize = 30, const char* tooltip = "");
    Button(const char* imagePath, float x, float y, float width, float height, const char* labelText, Color textColor, int fontSize = 30, const char* tooltip = "");
    Button(const Texture2D& texture, float x, float y, float width, float height, const char* labelText, Color textColor, int fontSize = 30, const char* tooltip = "");

    ~Button();

    void operator=(const Button& b);
    void update(float deltatime);
    void draw(Color tint = WHITE);

    void updatePos(Vector2 newPos);
    void updateScale(float newScale);
    bool IsClicked();
    bool IsMouseDown();
    bool IsHovered() const;
    Rectangle getBounds() const;
    Rectangle getScaledRect() const;
    Vector2 getPosition() const;
};

#endif
