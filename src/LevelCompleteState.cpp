#include "../headers/LevelCompleteState.h"

LevelCompleteState::LevelCompleteState() {
	score = 2000;
	int amount_button = 2;
	buttons.resize(amount_button);
	vector<string> txt(2*amount_button);
	string backgroundDir = "../assets/GUI/level" + to_string(Global::level.second) + "_button.png";
	background = LoadTexture(backgroundDir.c_str());
	completePanel = LoadTexture("../assets/GUI/LevelCompletePanel.png");
	txt[0] = string("../assets/GUI/Button.png");
	txt[1] = string("MENU");
	txt[2] = string("../assets/GUI/Button.png");
	txt[3] = string("NEXT LEVEL");
	buttons[0] = new Button(txt[0].c_str(), screenWidth / 3, screenHeight / 2, 250, 150, txt[1].c_str(), WHITE);
	buttons[1] = new Button(txt[2].c_str(), screenWidth / 3 + 300, screenHeight / 2, 250, 150, txt[3].c_str(), WHITE);
	font = LoadFont("../assets/font/knightwarrior.otf");
}
LevelCompleteState::~LevelCompleteState() {
	for (auto button : buttons)
		delete button;
	UnloadFont(font);
}
void LevelCompleteState::handleInput() {
	if (buttons[0]->IsClicked())
		Singleton<Game>::getInstance().addState(new MenuState);
	else if (buttons[1]->IsClicked())
		Singleton<Game>::getInstance().addState(new PlayState({Global::level.first, ++Global::level.second}));
}
void LevelCompleteState::update(float dt) {
	for (auto button : buttons)
		button->update(dt);
}
void LevelCompleteState::render() {
	DrawRectangleRec(Rectangle{ 0, 0, screenWidth, screenHeight }, Fade(BLACK, 0.4f));
	DrawTexturePro(completePanel,
		{ screenWidth/3-110, screenHeight/5, 740, 450 },
		{ screenWidth / 3-110, screenHeight / 5,740, 450 },
		{ 0,0 }, 0, WHITE);
	for (auto button : buttons)
		button->draw();
	DrawText("SCORE", screenWidth / 3, screenHeight/2 - 200, 40, BLACK);
	DrawText("COINS", screenWidth / 3, screenHeight/2 - 150, 40, BLACK);
	DrawText("LEVEL COMPLETE", screenWidth/5+75, screenHeight/5-100, 80, ORANGE);
}