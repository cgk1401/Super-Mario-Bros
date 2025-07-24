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
    Timer expansion_time;
    std::string Tooltip;
public:
    Button();
    Button(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color hoverCol, Color textCol, int fontSize = 20, const char* tooltip = "");
    Button(const char* imagePath, float x, float y, float width, float height, const char* labelText, Color textColor, int fontSize = 20, const char* tooltip = "");
    Button(const Texture2D& texture, float x, float y, float width, float height, const char* labelText, Color textColor, int fontSize = 20, const char* tooltip = "");

    ~Button();

    void operator=(const Button& b);
    void update(float deltatime);
    void draw();

    void updatePos(Vector2 newPos);
    bool IsClicked();
    bool IsMouseDown();
    Rectangle getBounds() const;
};

#endif
