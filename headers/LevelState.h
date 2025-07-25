#pragma once
#include <raylib.h>
#include <vector>
#include "GameState.h"
#include "MapEditor.h"
#include "Button.h"
#include <vector>
using namespace std;

class LevelState : public GameState {
private:
	Texture2D background;
	Button* backButton;
	vector<Button*> buttons;
	vector<Rectangle> levelSigns;
	Font font;

	vector<Map*> world;
public: 
	LevelState();
	~LevelState();
	void update(float deltatime);
	void render();
	bool allowUpdateBelow() override { return false; }
};
