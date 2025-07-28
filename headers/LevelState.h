#pragma once
#include <raylib.h>
#include <vector>
#include "GameState.h"
#include "Button.h"
using namespace std;

class LevelState : public GameState {
private:
	Texture2D background;
	Button* backButton;
	vector<Button*> buttons;
	vector<Rectangle> levelSigns;
	Font font;
public: 
	LevelState();
	~LevelState();
	void update(float deltatime) override;
	void render() override;
	bool allowUpdateBelow() override { return false; }
};
