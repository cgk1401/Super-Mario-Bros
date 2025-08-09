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
	int display_score = 0;
	int level;
	HUD* hud;
	Character* player;
	Map* map;

public: 
	LevelCompleteState(HUD* _hud, Character* _player, Map* _map);
	~LevelCompleteState();
	void handleInput() override;
	void update(float) override;
	void render() override;
	bool allowUpdateBelow() override { return false; }
};
