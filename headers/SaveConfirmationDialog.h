#pragma once

#include "GameState.h"
#include "MapEditor.h"
#include <vector>
using namespace std;

class SaveConfirmationDialog : public GameState {
private :
    Texture2D buttonPanel;
    Vector2 position;

    vector <Button*> buttonsettings;
    // 1 : save, 2 : no, 3 cancel

    vector <Button*> createButtons(Texture2D& buttonPanel,
        int amount_buttons, 
        const char* labelsButtons[], 
        vector <Color> colorButton, 
        vector <Color> colorText,
        vector <Color> hoverButton);
    const char* text = "DO YOU WANT TO SAVE YOUR WORK?";
    Vector2 posistionText;


public :
	SaveConfirmationDialog();
	~SaveConfirmationDialog();

    vector <bool> buttonclick;

    void handleInput() override;
    void update(float deltatime) override;
    void render() override;
    bool allowUpdateBelow() override { return false; }
};
