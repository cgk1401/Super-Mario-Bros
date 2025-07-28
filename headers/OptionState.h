#pragma once
#include <raylib.h>
#include <vector>
#include "Global.h"
#include "GameState.h"
#include "Button.h"
#include "LevelState.h"
#include "PlayState.h"
using std::vector;

class OptionState : public GameState {
private: 
	vector<Button*> buttons;
	Button* backButton;
	Font font;
	Texture2D background;
public:
	OptionState();
	~OptionState();
	void update(float) override;
	void render() override;
};