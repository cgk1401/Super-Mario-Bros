#include "../headers/LevelState.h"
#include "../headers/Global.h"
#include "../headers/Game.h"
#include "../headers/MenuState.h"

LevelState::LevelState(bool _isEditorMode) {
	isEditorMode = _isEditorMode;
	background = resizedImage("../assets/GUI/Menu background.png", screenWidth, screenHeight);
	int amount_button = 4;
	buttons.resize(amount_button);
	levelSigns.resize(amount_button);
	levelSigns[0] = Rectangle{ screenWidth * 0.15f, screenHeight * 0.15f, 100, 40 };
	levelSigns[1] = Rectangle{ screenWidth * 0.6f, screenHeight * 0.15f, 100, 40 };
	levelSigns[2] = Rectangle{ screenWidth * 0.15f, screenHeight * 0.6f, 100, 40 };
	levelSigns[3] = Rectangle{ screenWidth * 0.6f, screenHeight * 0.6f, 100, 40 };
	buttons[0] = new Button("../assets/GUI/level1_button.png", screenWidth * 0.15f, screenHeight * 0.15f, 400, 300, "", WHITE);
	buttons[1] = new Button("../assets/GUI/level2_button.png", screenWidth * 0.6f, screenHeight * 0.15f, 400, 300, "", WHITE);
	buttons[2] = new Button("../assets/GUI/level3_button.png", screenWidth * 0.15f, screenHeight * 0.6f, 400, 300, "", WHITE);
	buttons[3] = new Button("../assets/GUI/level4_button.png", screenWidth * 0.6f, screenHeight * 0.6f, 400, 300, "", WHITE);
	backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);
	font = LoadFont("../assets/font/knightwarrior.otf");
}
LevelState::~LevelState() {
	delete backButton;
	for (auto& button : buttons) {
		delete button;
	}
	UnloadFont(font);
	UnloadTexture(background);
}
void LevelState::update(float deltatime) {
	Singleton<SoundManager>::getInstance().updateMusic();
	for (auto& button : buttons) {
		button->update(deltatime);
	}
	backButton->update(deltatime);
	if (buttons[0]->IsClicked()) {
		// Load Level 1
		if(isEditorMode) Singleton<Game>::getInstance().changeState(new MapEditor({1,1}));
		else 			 Singleton<Game>::getInstance().changeState(new PlayState({1,1}));
		
	}
	else if (buttons[1]->IsClicked()) {
		// Load Level 2
		if(isEditorMode) Singleton<Game>::getInstance().changeState(new MapEditor({1,2}));
		else 			 Singleton<Game>::getInstance().changeState(new PlayState({1,2}));
	}
	else if (buttons[2]->IsClicked()) {
		// Load Level 3
		if(isEditorMode) Singleton<Game>::getInstance().changeState(new MapEditor({1,3}));
		else 			 Singleton<Game>::getInstance().changeState(new PlayState({1,3}));
	}
	else if (buttons[3]->IsClicked()) {
		// Load Level 4
		if(isEditorMode) Singleton<Game>::getInstance().changeState(new MapEditor({1,4}));
		else 			 Singleton<Game>::getInstance().changeState(new PlayState({1,4}));
	}	
	else if (backButton->IsClicked()) {
		Singleton<Game>::getInstance().pop();
	}

}
void LevelState::render() {
	DrawTexture(background, 0, 0, WHITE);
	DrawRectangleRec(Rectangle{ 0, 0, screenWidth, screenHeight }, Fade(GRAY, 0.4f));
	
	backButton->draw();
	for (auto& button : buttons) {
		button->draw();
	}
	// Render level signs
	for (size_t i = 0; i < levelSigns.size(); ++i) {
		DrawRectangleRec(levelSigns[i], WHITE);
		DrawText(TextFormat("Level %zu", i + 1), levelSigns[i].x + 10, levelSigns[i].y + 10, 20, BLACK);
	}
}