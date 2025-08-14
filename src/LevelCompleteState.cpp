#include "../headers/LevelCompleteState.h"

LevelCompleteState::LevelCompleteState(HUD* _hud, Character* _player, Map* _map) {
	hud = _hud;
	player = _player;
	map = _map;
	int amount_button = 2;
	buttons.resize(amount_button);
	vector<string> txt(amount_button);
	//string backgroundDir = "../assets/GUI/level" + to_string(Global::level.second) + "_button.png";
	background = LoadTexture("../assets/GUI/level complete.png");
	//completePanel = LoadTexture("../assets/GUI/LevelCompletePanel.png");
	txt[0] = string("MENU");
	txt[1] = map->getLevel().second != 4 ? ("NEXT") : "RESTART";
	buttons[0] = new Button(Singleton<TextureManager>::getInstance().load(TextureType::BUTTON), screenWidth *0.33f, screenHeight * 0.72f, 200, 120, txt[0].c_str(), WHITE);
	buttons[1] = new Button(Singleton<TextureManager>::getInstance().load(TextureType::BUTTON), screenWidth *0.33f + 200 + 20, screenHeight * 0.72f, 200, 120, txt[1].c_str(), WHITE);
	font = LoadFont("../assets/font/knightwarrior.otf");

	

	score = hud->getScore();
	level = map->getLevel().second;

	Singleton<SoundManager>::getInstance().play(SoundType::lEVEL_COMPLETE);

}
LevelCompleteState::~LevelCompleteState() {
	for (auto button : buttons)
		delete button;
	UnloadFont(font);
}


void LevelCompleteState::handleInput() {
	if (buttons[0]->IsClicked())
		Singleton<Game>::getInstance().changeState(new MenuState);
	else if (buttons[1]->IsClicked())
	{
        player->isControlled = false;
        pair<int, int> currentLevel = map->getLevel();
        pair<int, int> newLevel = {currentLevel.first, currentLevel.second + 1};
        if (newLevel.second <= 4) {
             Singleton<Game>::getInstance().changeState(new PlayState(newLevel, hud, player));
        }
		else Singleton<Game>::getInstance().changeState(new PlayState({1,1}));


	}
}
void LevelCompleteState::update(float dt) {
	for (auto button : buttons)
		button->update(dt);

	display_score += 100;
	if(display_score > score){
		display_score = score;
	}
	else{
		Singleton<SoundManager>::getInstance().play(SoundType::BEEP);
	}

}
void LevelCompleteState::render() {
	DrawRectangleRec(Rectangle{ 0, 0, screenWidth, screenHeight }, Fade(BLACK, 0.4f));
	const float scale = 1;
	Rectangle dest = {screenWidth / 2 - (float)background.width * scale/ 2, screenHeight/2 - (float)background.height * scale / 2,background.width * scale, background.height * scale };
	DrawTexturePro(background,
				{0,0, (float)background.width, (float)background.height},
				dest,
				{0,0},
				0,
				WHITE);
	// DrawTexturePro(completePanel,
	// 	{ screenWidth/3-110, screenHeight/5, 740, 450 },
	// 	{ screenWidth / 3-110, screenHeight / 5,740, 450 },
	// 	{ 0,0 }, 0, WHITE);
	string scoreStr = to_string(display_score);
	 float textFontSize = 50;
    float spacing = 5;
    Vector2 text = MeasureTextEx(font, scoreStr.c_str(), textFontSize, spacing);
    
    float textX = screenWidth / 2  - (text.x) / 2;
    float textY = 490;
	DrawTextEx(font, scoreStr.c_str(), {textX ,textY}, textFontSize, spacing, WHITE );
	for (auto button : buttons)
		button->draw();
	string levelStr = "Level " + to_string(level);
	DrawTextEx(font, levelStr.c_str(), {screenWidth / 2 -100 ,260}, 70, 5, WHITE);
	//DrawText("SCORE", screenWidth / 3, screenHeight/2 - 200, 40, BLACK);
	//DrawText("COINS", screenWidth / 3, screenHeight/2 - 150, 40, BLACK);
	//DrawText("LEVEL COMPLETE", screenWidth/5+75, screenHeight/5-100, 80, ORANGE);
}