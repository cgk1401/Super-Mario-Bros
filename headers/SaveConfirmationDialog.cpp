#include "SaveConfirmationDialog.h"
#include "../headers/TextureManager.h"
#include "../headers/Singleton.h"
#include "../headers/Global.h"

vector<Button*> SaveConfirmationDialog::createButtons(Texture2D& buttonPanel,
	int amount_buttons,
	const char* labelsButtons[], 
	vector<Color> colorButton,
	vector<Color> colorText,
	vector<Color> hoverButton) {

	vector <Button*> buttons(amount_buttons);

	float width_buttonPanel = buttonPanel.width;
	float height_buttonPanel = buttonPanel.height;

	Vector2 positionButtonPanel;
	positionButtonPanel.x = float(screenWidth - width_buttonPanel) / 2;
	positionButtonPanel.y = float(screenHeight - height_buttonPanel) - 50;

	float LEFT_MARGIN = 30.0f;

	float BUTTON_SPACING = 20.0f;

	float BUTTON_WEIGHT = (width_buttonPanel - BUTTON_SPACING * (amount_buttons -1) - 2 * LEFT_MARGIN) / amount_buttons;
	float BUTTON_HEIGHT = 40.0f;

	float drawStartPos_Y = positionButtonPanel.y + 200;
	float drawStartPos_X = positionButtonPanel.x + LEFT_MARGIN;

	for (int i = 0; i < 3; i++) {
		buttons[i] = new Button(
			drawStartPos_X + i * (BUTTON_WEIGHT + BUTTON_SPACING),
			drawStartPos_Y,
			BUTTON_WEIGHT,
			BUTTON_HEIGHT,
			labelsButtons[i],
			colorButton[i],
			hoverButton[i],
			colorText[i],
			25,
			"");
	}
	return buttons;
}

SaveConfirmationDialog::SaveConfirmationDialog() {
	buttonPanel = Singleton<TextureManager>::getInstance().load(TextureType::buttonPanel);

	int width_buttonPanel = buttonPanel.width;
	int height_buttonPanel = buttonPanel.height;
	position.x = float(screenWidth - width_buttonPanel) / 2;
	position.y = float(screenHeight - height_buttonPanel) - 50;

	const char* labelButtons[3] = { "Save", "No", "Cancel" };
	vector <Color> colorButtons = { RED, GRAY, GRAY };
	vector <Color> colorText = { WHITE, BLACK, BLACK };
	vector <Color> hoverButton = { DARKBLUE, DARKBLUE, DARKBLUE };

	buttonsettings = createButtons(
		buttonPanel,
		3,
		labelButtons,
		colorButtons,
		colorText,
		hoverButton
	);
}

SaveConfirmationDialog::~SaveConfirmationDialog() {
	UnloadTexture(buttonPanel);
	for (int i = 0; i < buttonsettings.size(); i++) delete buttonsettings[i];
}

void SaveConfirmationDialog::update(float deltatime) {
	for (int i = 0; i < 3; i++) {
		buttonsettings[i]->update(deltatime);
	}
}

void SaveConfirmationDialog::render() {
	DrawTexture(buttonPanel, position.x, position.y, WHITE);
	for (int i = 0; i < 3; i++) {
		buttonsettings[i]->draw();
	}
}
