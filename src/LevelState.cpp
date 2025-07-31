#include "../headers/LevelState.h"
#include "../headers/Global.h"
#include "../headers/Game.h"
#include "../headers/MenuState.h"

LevelState::LevelState(bool _isEditorMode) {
	isEditorMode = _isEditorMode;
	if(isEditorMode) background = Singleton<TextureManager>::getInstance().load(TextureType::BACKGROUND_1);
	else background = Singleton<TextureManager>::getInstance().load(TextureType::BACKGROUND_2);
	int amount_button = 4;
	buttons.resize(amount_button);
	const int height = 600;
	workRect = { 0, screenHeight / 2 - height / 2, screenWidth, height };
	levelSigns.resize(amount_button);
	for(int i = 0; i < buttons.size(); i++){
		string filename = "../assets/GUI/levelselect_1-" + to_string(i + 1) + ".png";
		buttons[i] = new Button(filename.c_str(), workRect.x + (float) i * 320, workRect.y, 366, 600, "", WHITE);
		levelSigns[i] = { workRect.x + (float)i * 320 + buttons[i]->getBounds().width / 2, workRect.y + workRect.height, 100 ,40 };
	}
	backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);
	font = LoadFont("../assets/font/knightwarrior.otf");
	
}
LevelState::~LevelState() {
	delete backButton;
	for (auto& button : buttons) {
		delete button;
	}
	UnloadFont(font);
}

void LevelState::handleInput() {
	if (buttons[0]->IsClicked()) {
		// Load Level 1
		if (isEditorMode) Singleton<Game>::getInstance().changeState(new MapEditor({ 1,1 }));
		else 			 Singleton<Game>::getInstance().changeState(new PlayState({ 1,1 }));
		shouldExit = true;

	}
	else if (buttons[1]->IsClicked()) {
		// Load Level 2
		if (isEditorMode) Singleton<Game>::getInstance().changeState(new MapEditor({ 1,2 }));
		else 			 Singleton<Game>::getInstance().changeState(new PlayState({ 1,2 }));
		shouldExit = true;

	}
	else if (buttons[2]->IsClicked()) {
		// Load Level 3
		if (isEditorMode) Singleton<Game>::getInstance().changeState(new MapEditor({ 1,3 }));
		else 			 Singleton<Game>::getInstance().changeState(new PlayState({ 1,3 }));
		shouldExit = true;

	}
	else if (buttons[3]->IsClicked()) {
		// Load Level 4
		if (isEditorMode) Singleton<Game>::getInstance().changeState(new MapEditor({ 1,4 }));
		else 			 Singleton<Game>::getInstance().changeState(new PlayState({ 1,4 }));
		shouldExit = true;

	}
	else if (backButton->IsClicked()) {
		Singleton<Game>::getInstance().pop();
		shouldExit = true;

	}
}
void LevelState::update(float deltatime) {
	Singleton<SoundManager>::getInstance().updateMusic();
	for (auto& button : buttons) {
		button->update(deltatime);
	}
	backButton->update(deltatime);

	///_______________________BUTTON CLICK ANIMATION_______________________________
    int hoveredIndex = -1;
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i]->IsHovered()) {
            hoveredIndex = i;
            break;
        }
    }
    const float distance = 320;
    for (int i = 0; i < buttons.size(); i++) {
        float offset = 0;
        if (hoveredIndex != -1 && i != hoveredIndex) {
            int dist = abs(i - hoveredIndex);
            offset = dist == 1 ? 30 : (dist == 2 ? 15 : 0); 
            if (i < hoveredIndex) offset *= -1;
        }

        Vector2 targetPos = {
            workRect.x + i * distance + offset,
            buttons[i]->getBounds().y
        };

        Vector2 currentPos = buttons[i]->getPosition();
        float posX = approach(currentPos.x, targetPos.x, 2);
        buttons[i]->updatePos({ posX, currentPos.y });
		levelSigns[i].x = posX + buttons[i]->getBounds().width / 2;
    }
	///___________________________________________________________________________
	
}
void LevelState::render() {
	///_____________________________BACKGROUND_______________________________________
	DrawTexturePro(background,
			{0,0, (float)background.width,(float) background.height},
			{0,0, screenWidth, screenHeight},
			 {0,0}, 0, WHITE);
	DrawRectangleRec(Rectangle{ 0, 0, screenWidth, screenHeight }, Fade(BLACK, 0.4f));
	DrawRectangleRec(workRect, Fade(DARKBROWN, 0.7f));

	///____________________________MAP LEVEL OPTIONS___________________________________________
	int threshold = 5;
	int line_height = 3;
	DrawLineEx({ workRect.x, workRect.y - threshold }, { screenWidth, workRect.y - threshold }, line_height, WHITE);
	DrawLineEx({workRect.x, workRect.y + workRect.height + threshold}, { screenWidth, workRect.y + workRect.height + threshold }, line_height, WHITE);
	backButton->draw();
	for (auto& button : buttons) {
		button->draw();
	}

	///____________________________LEVEL SIGNS___________________________________________
	for (size_t i = 0; i < levelSigns.size(); ++i) {
		DrawRectangleRec(levelSigns[i], WHITE);
		DrawTextEx(font, TextFormat("Level %zu", i + 1), {levelSigns[i].x + 10, levelSigns[i].y + 10},20, 5, BLACK);
	}

	
}