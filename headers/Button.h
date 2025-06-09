#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <string>

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

public:
    Button();
    Button(float x, float y, float width, float height, const char* labelText, Color buttonColor, Color hoverCol, Color textCol, int fontSize = 20);
    Button(const char* imagePath, float x, float y, float width, float height, const char* labelText, Color textColor, int fontSize = 20);
    ~Button();

    void operator=(const Button& b);
    void update();
    void draw();
    bool IsClicked();
    Rectangle getBounds() const;
};

#endif
