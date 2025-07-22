#include "../headers/GameState.h"
#include "../headers/Global.h"

ButtonLayoutConfig::ButtonLayoutConfig(int amount_button) {
    this->amount_button = amount_button;
   
    MARGIN_ON = screenHeight * 0.1f;
    MENU_BUTTON_HEIGHT = screenHeight - 2 * MARGIN_ON - 100.0f - 40;

    BUTTON_MARGIN_X = screenWidth * 0.35f;
    FIRST_POSITION_Y_BUTTON = MARGIN_ON + 100.0f;
    BUTTON_SPACING = 15.0f;

    BUTTON_HEIGHT = float(MENU_BUTTON_HEIGHT - BUTTON_SPACING * 2) / amount_button;
    BUTTON_WIDTH = screenWidth / 3;
}

std::vector<Button*> CreateButtons(const char* buttonLabels[], const ButtonLayoutConfig& other) {
    vector <Button*> buttons(other.amount_button);
    for (int i = 0; i < other.amount_button; i++) {
        buttons[i] = new Button(Singleton<TextureManager>::getInstance().load(TextureType::BUTTON), 
            other.BUTTON_MARGIN_X, 
            other.FIRST_POSITION_Y_BUTTON + i * (other.BUTTON_HEIGHT + other.BUTTON_SPACING),
            other.BUTTON_WIDTH, 
            other.BUTTON_HEIGHT, 
            buttonLabels[i], WHITE, 30);
    }
    return buttons;
}