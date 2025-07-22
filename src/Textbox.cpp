#include "../headers/Textbox.h"

TextBox::TextBox(float x, float y, float width, float height, const char* labelText, 
        Color buttonColor, Color hoverCol, Color textCol) { 
    bound = {x, y, width, height};
    inputText = {""};  
    SubIndex = {0};
    active = false;  
    nums.clear();  
    currentIndex = 0; 
    maxVisibleLength = 15; 
    startColumnIndex = 0;
    textColor = textCol;
}
void TextBox::update(){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 mousePos = GetMousePosition();
    active = (mousePos.x >= bound.x && mousePos.x <=  bound.x + bound.width && mousePos.y >= bound.y && mousePos.y <= bound.y + bound.height);
    }

    if(active){
        if(IsKeyPressed(KEY_DOWN)){

            currentIndex++;
            if(currentIndex >= inputText.size()) currentIndex = inputText.size() - 1;
            if(currentIndex - startRowIndex > 2) startRowIndex++;
            startColumnIndex = 0;
        }

        if(IsKeyPressed(KEY_UP)){
            currentIndex--;
            if(currentIndex < 0) currentIndex = 0;
            if(currentIndex - startRowIndex < 0) startRowIndex--;
            startColumnIndex = 0;
        }

        if (!SubIndex.empty() && currentIndex >= 0 && currentIndex < SubIndex.size()) { 
            if(IsKeyPressed(KEY_LEFT)){
                SubIndex[currentIndex]--;
                if(SubIndex[currentIndex] < 0) {
                    SubIndex[currentIndex] = 0;
                    if(startColumnIndex > 0 && SubIndex[currentIndex] < startColumnIndex) startColumnIndex--;
                } else if (SubIndex[currentIndex] < startColumnIndex) {
                    startColumnIndex = SubIndex[currentIndex];
                }
            }

            if (!inputText.empty() && currentIndex >= 0 && currentIndex < inputText.size()) { 
                if(IsKeyPressed(KEY_RIGHT)){
                    SubIndex[currentIndex]++;
                        if(SubIndex[currentIndex] > inputText[currentIndex].size()) {
                        SubIndex[currentIndex] = inputText[currentIndex].size();
                    } 
                    else if (SubIndex[currentIndex] >= startColumnIndex + maxVisibleLength) {
                        startColumnIndex++;
                    }
                }
            }
        }

    }
}
void TextBox::Draw()  { 

    Color col = active ? RED : WHITE;
    DrawRectangleRec(bound, col);
    HandleInput();
    int cnt = 0;
    for(int i = startRowIndex; i < inputText.size() && i < startRowIndex + 3; i++){
        string currentText = inputText[i];
        int subIndex = (i == currentIndex && !SubIndex.empty() && i < SubIndex.size()) ? SubIndex[i] : currentText.size();

        string visibleText = "";
        int cursorPositionInVisibleText = -1;

        if (!currentText.empty()) {
            int endIndex = min((int)currentText.size(), startColumnIndex + maxVisibleLength);
            int length = endIndex - startColumnIndex;
            if (length > 0) {
                visibleText = currentText.substr(startColumnIndex, length);
            } else {
                visibleText = "";
            }
    
            if (i == currentIndex) {
                cursorPositionInVisibleText = subIndex - startColumnIndex;
                if (cursorPositionInVisibleText < 0 || cursorPositionInVisibleText > visibleText.size()) {
                    cursorPositionInVisibleText = visibleText.size(); 
                }
            }
        } else if (i == currentIndex) {
                cursorPositionInVisibleText = 0;
        }
        string displayText = visibleText;
        if (active && i == currentIndex && ((int)(GetTime() * 2) % 2 == 0) && cursorPositionInVisibleText >= 0 && cursorPositionInVisibleText <= displayText.size()) {
        displayText.insert(displayText.begin() + cursorPositionInVisibleText, '|');
        }

        float lineHeight = 25;
        // Vector2 textHeight = MeasureTextEx(FONT, displayText.c_str(), 25, 1);
        
        Font FONT = GetFontDefault();
        DrawTextEx(FONT, displayText.c_str(), {bound.x + 5 , bound.y + 5  + cnt * lineHeight}, 25, 2, textColor);
        cnt++;
        
    }
}

void TextBox::HandleInput() {
if (active) {
    int key = GetCharPressed();
    if (!inputText.empty() && currentIndex >= 0 && currentIndex < inputText.size() &&
        !SubIndex.empty() && currentIndex >= 0 && currentIndex < SubIndex.size()) { 
        while (key > 0 ) {
           
                int idx = SubIndex[currentIndex];
                inputText[currentIndex].insert(inputText[currentIndex].begin() + idx,(char)key);
                SubIndex[currentIndex]++;
                if (SubIndex[currentIndex] >= startColumnIndex + maxVisibleLength) {
                    startColumnIndex++;
                }
            
            key = GetCharPressed();
        }
    }

    if(IsKeyPressed(KEY_ENTER)){
        inputText.push_back("");
        SubIndex.push_back(0);
        currentIndex++;
            if(currentIndex - startRowIndex > 2) startRowIndex++;
            startColumnIndex = 0;
    }

    if (!inputText.empty() && currentIndex >= 0 && currentIndex < inputText.size() &&
        !SubIndex.empty() && currentIndex >= 0 && currentIndex < SubIndex.size()) { 
        if(IsKeyPressed(KEY_BACKSPACE)){
            if (SubIndex[currentIndex] > 0) {
                SubIndex[currentIndex]--;
                int idx = SubIndex[currentIndex];
                inputText[currentIndex].erase(inputText[currentIndex].begin() + idx);
                if (SubIndex[currentIndex] < startColumnIndex) {
                    startColumnIndex--;
                    if (startColumnIndex < 0) startColumnIndex = 0;
                }
            } else if (inputText.size() > 1) { 
                inputText.erase(inputText.begin() + currentIndex);
                SubIndex.erase(SubIndex.begin() + currentIndex);
                currentIndex--;
                if (currentIndex < 0) currentIndex = 0;
                if (!SubIndex.empty() && currentIndex >= 0 && currentIndex < SubIndex.size()) {
                    SubIndex[currentIndex] = inputText[currentIndex].size();
                    startColumnIndex = max(0, (int)inputText[currentIndex].size() - maxVisibleLength); 
                }
                if(currentIndex - startRowIndex < 0) startRowIndex--;
            }
            else startColumnIndex = 0;
        }

    }
}
}




void TextBox::reset(){
    active = false;
    inputText.clear();
    inputText = {""};
    currentIndex = 0;
    SubIndex.clear();
    SubIndex.push_back(0);
    startRowIndex = 0;
    startColumnIndex = 0;
    active = false;
    nums.clear();
}

void TextBox::resetTextbox(){
    active = false;
    inputText.clear();
    inputText = {""};
    currentIndex = 0;
    SubIndex.clear();
    SubIndex.push_back(0);
    startRowIndex = 0;
    startColumnIndex = 0;
    active = false;
// nums.clear();
}


string TextBox::getText() const{
    return inputText[0];
}