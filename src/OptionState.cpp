#include "../headers/OptionState.h"
#include "../headers/CharacterSelection.h"
OptionState::OptionState() {
	const int amount_button = 3;
	buttons.resize(amount_button);
	ButtonLayoutConfig cfg(amount_button);
	const char* buttonLabels[amount_button] = {"NEW GAME", "CONTINUE", "LEVEL"};
	buttons = CreateButtons(buttonLabels, cfg);

	backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);
	font = LoadFont("../assets/font/knightwarrior.otf");
	background = LoadTexture("../assets/GUI/option_background.png");
}
OptionState::~OptionState() {
	for (auto& button : buttons)
		delete button;
	delete backButton;
	UnloadTexture(background);
	UnloadFont(font);
}
void OptionState::update(float deltatime) {
	Singleton<SoundManager>::getInstance().updateMusic();
	for (auto& button : buttons)
		button->update(deltatime);
	backButton->update(deltatime);
	if (buttons[0]->IsClicked()) {
		Singleton<Game>::getInstance().addState(new CharacterSelection());
	}
	else if (buttons[1]->IsClicked()) {
		//CONTINUE
	}
	else if (buttons[2]->IsClicked()) {
		Singleton<Game>::getInstance().replaceState(new LevelState());
	}
	else if (backButton->IsClicked()) {
		Singleton<Game>::getInstance().pop();
	}
}
void OptionState::render() {
	DrawTexturePro(background,
				{0,0, (float)background.width,(float) background.height},
				{0,0, screenWidth, screenHeight},
				 {0,0}, 0, WHITE);
	for (auto& button : buttons)
		button->draw();
	backButton->draw();
}