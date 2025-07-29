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
	bool isEditorMode;

	Rectangle workRect;
public: 
	LevelState(bool isEditorMode = false);
	~LevelState();
	void update(float deltatime) override;
	void render() override;
	bool allowUpdateBelow() override { return false; }
};
