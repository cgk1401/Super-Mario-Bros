#include "KeyBindingState.h"
#include "AudioSettingsMenu.h"
#include "Global.h"
Controls KeyBindingState::controls;

 KeyBindingState::KeyBindingState() :selectedIndex(0), waitingForKey(false) {
    texture = LoadTexture("../assets/GUI/keybinding.png");
    buttons.resize(4);
    float w = 350;
    float h = 60;
    for(int i = 0; i < 4; i++){
        buttons[i] = {800, 250 + (h + 31) * i, w, h};
    }
    FONT  = Singleton<TextureManager>::getInstance().load(MyFontType::KNIGHT_WARRIOR);
    backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);
	audioButton = {(screenWidth - texture.width) / 2.0f + 23, (screenHeight -  texture.height) / 2.0f, 93, 93};

}
void KeyBindingState::handleInput()  {
    if(backButton->IsClicked()){
        Singleton<Game>::getInstance().pop();
        shouldExit = true;
    }
    Vector2 mousePos = GetMousePosition();
    for (int i = 0; i < buttons.size(); i++) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, buttons[i])) {
            Singleton<SoundManager>::getInstance().play(SoundType::CLICK_BUTTON);

            if(selectedIndex != i){
                waitingForKey = true;
            }
            else waitingForKey = !waitingForKey;
            selectedIndex = i;
        }
    }
     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, audioButton)){
        Singleton<SoundManager>::getInstance().play(SoundType::CLICK_BUTTON);
        Singleton<Game>::getInstance().replaceState(new AudioSettingsMenu);
     }

}
void KeyBindingState::update(float dt)  {
    backButton->update(dt);
    Singleton<SoundManager>::getInstance().updateMusic(dt);

    if (waitingForKey) {
        int newKey = GetKeyPressed();
        keyPress = GetCharPressed();
        if (newKey != 0) {
            setControlKey(selectedIndex, newKey);
            waitingForKey = false;
        }
        //return;
    }

   /* if (IsKeyPressed(KEY_DOWN)) selectedIndex++;
    if (IsKeyPressed(KEY_UP))   selectedIndex--;*/

    if(selectedIndex < 0) selectedIndex = 0;
    else if (selectedIndex > 3) selectedIndex = 3;
    
}

void KeyBindingState::render()  {
    DrawRectangle(0,0,screenWidth, screenHeight, Fade(BLACK, 0.6f));
    DrawTexturePro(texture,
                {0,0,(float)texture.width, (float)texture.height},
                {(screenWidth - texture.width) / 2.0f,(screenHeight -  texture.height) / 2.0f, (float)texture.width,  (float)texture.height},
                {0,0},
                0,
                WHITE);
    //DrawText("KEY BINDING", 50, 50, 30, YELLOW);

    //const char* actions[] = { "Move Left", "Move Right", "Jump", "Crouch" };
    int keys[] = { controls.moveLeft, controls.moveRight, controls.jump, controls.crouch };

    for (int i = 0; i < 4; i++) {
        DrawRectangleRec(buttons[i], Fade(BLACK, 0.7f));
        float alpha = (i== selectedIndex) ? 0.7f : 0.0f;
        DrawRectangleLinesEx(buttons[i], 2, Fade(RED, alpha));
        Color col = (i == selectedIndex) ? RED : WHITE;
        //DrawText(actions[i], 50, 100 + i * 40, 20, col);
        string keyName = GetKeyNameCustom(keys[i]);
        if(selectedIndex == i){
            if(waitingForKey) keyName = "Press a new key...";
        }
        Rectangle dest = buttons[i];
        float textFontSize = 40;
        float spacing = 2;
        Vector2 text = MeasureTextEx(FONT, keyName.c_str(), textFontSize, spacing);
        float textX = dest.x + (dest.width - text.x) / 2;
        float textY = dest.y + (dest.height - text.y) / 2;
        DrawTextEx(FONT, keyName.c_str(), {textX, textY}, textFontSize, spacing, col);
    }

    backButton->draw();
}

void KeyBindingState::setControlKey(int index, int newKey) {
    switch (index) {
    case 0: controls.moveLeft = newKey; break;
    case 1: controls.moveRight = newKey; break;
    case 2: controls.jump = newKey; break;
    case 3: controls.crouch = newKey; break;
    }
}