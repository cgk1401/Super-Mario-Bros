#pragma once 
#include <raylib.h>
#include <vector>
#include <string>
#include "GameState.h"
#include "Button.h"
#include "Global.h"
#include "PlayState.h"
#include "MenuState.h"
using namespace std;

class LevelCompleteState : public GameState {
private:
	Texture background;
	Texture completePanel;
	Font font;
	vector<Button*> buttons;
	int score; // Score for the level
public: 
	LevelCompleteState();
	~LevelCompleteState();
	void handleInput() override;
	void update(float) override;
	void render() override;
	bool allowUpdateBelow() override { return false; }
};
