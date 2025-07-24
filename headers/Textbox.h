#pragma once
#include "Button.h"
#include <string>
#include <vector>
using namespace std;

class TextBox {
private:
    Rectangle bound;
    vector<string> inputText;
    int currentIndex;
    int startRowIndex;
    int startColumnIndex;
    int maxVisibleLength;
    bool active;
    vector<int> SubIndex;
    vector<int> nums;

    Color textColor;
public:
    TextBox(){}

    TextBox(float x, float y, float width, float height, const char* labelText, 
            Color buttonColor, Color hoverCol, Color textCol);
    void update();
    void Draw()  ;

    void HandleInput();

    string getText() const;
    void reset();
    void resetTextbox();
};