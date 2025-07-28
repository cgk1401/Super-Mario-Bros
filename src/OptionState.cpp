#include "../headers/OptionState.h"

OptionState::OptionState() {
	const int amount_button = 3;
	buttons.resize(amount_button);
	ButtonLayoutConfig cfg(amount_button);
	const char* buttonLabels[amount_button] = {"NEW GAME", "CONTINUE", "LEVEL"};
	buttons = CreateButtons(buttonLabels, cfg);

	backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);
	font = LoadFont("../assets/font/knightwarrior.otf");
	background = resizedImage("../assets/GUI/Menu Background.png", screenWidth, screenHeight);
}
OptionState::~OptionState() {
	for (auto& button : buttons)
		delete button;
	delete backButton;
	UnloadTexture(background);
	UnloadFont(font);
}
void OptionState::update(float deltatime) {
	for (auto& button : buttons)
		button->update(deltatime);
	backButton->update(deltatime);
	if (buttons[0]->IsClicked()) {
		Singleton<Game>::getInstance().clear();
		Singleton<Game>::getInstance().addState(new PlayState());
	}
	else if (buttons[1]->IsClicked()) {
		//CONTINUE
	}
	else if (this->buttons[2]->IsClicked()) {
		Singleton<Game>::getInstance().addState(new LevelState);
	}
	else if (backButton->IsClicked()) {
		Singleton<Game>::getInstance().pop();
	}
}
void OptionState::render() {
	DrawTexture(background, 0, 0, WHITE);
	for (auto& button : buttons)
		button->draw();
	backButton->draw();
}