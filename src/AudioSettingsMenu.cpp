#include "AudioSettingsMenu.h"
#include "SoundManager.h"
#include <raylib.h>
#include <algorithm>
#include <cstdio>
#include "MenuState.h"
#include "KeyBindingState.h"
AudioSettingsMenu::AudioSettingsMenu() {
	background = Singleton<TextureManager>::getInstance().load(TextureType::BACKGROUND_1);
	audioPanel = Singleton<TextureManager>::getInstance().load(TextureType::AUDIOPANEL);
	currentmusicVolume = Singleton<SoundManager>::getInstance().getmusicVolume();
	currentsoundVolume = Singleton<SoundManager>::getInstance().getsoundVolume();

	float widthPanel = audioPanel.width;
	float heightPanel = audioPanel.height;

	positionPanel.x = (screenWidth - widthPanel) * float(1) / 2;
	positionPanel.y = (screenHeight - heightPanel) * float(1) / 2;
	backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);

	float widthslider = 400;
	float heightslider = 20;
	float widthText = MeasureText(musicText, 20);

	float spacingX = (widthPanel - widthslider - LEFT_MARGIN - widthText) * float(1) / 2;
	float spacingY = (heightPanel - heightslider * 2) * float(1) / 3;
	musicSlider = { positionPanel.x + LEFT_MARGIN + widthText + spacingX, positionPanel.y + spacingY, widthslider, heightslider };
	soundSlider = { positionPanel.x + LEFT_MARGIN + widthText + spacingX, positionPanel.y + spacingY * 2 + heightslider, widthslider, heightslider };
	musicSliderHandle = { musicSlider.x + widthslider * currentmusicVolume, musicSlider.y - 10, 10, 40 };
	soundSliderHandle = { soundSlider.x + widthslider * currentsoundVolume, soundSlider.y - 10, 10, 40 };
	draggingMusicSlider = false;
	draggingSoundSlider = false;

	keybindingButton = {positionPanel.x + 23, positionPanel.y + 101, 93, 93};
}

AudioSettingsMenu::~AudioSettingsMenu() {
	delete backButton;
}


void AudioSettingsMenu::handleInput() {

	if (CheckCollisionPointRec(GetMousePosition(), musicSliderHandle) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		draggingMusicSlider = true;
	}
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		draggingMusicSlider = false;
	}



	if (CheckCollisionPointRec(GetMousePosition(), soundSliderHandle) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		draggingSoundSlider = true;
	}
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		draggingSoundSlider = false;
	}

	if (backButton->IsClicked()) {
		Singleton<Game>::getInstance().pop();
		shouldExit = true;
	}

	 if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), keybindingButton)){
            Singleton<SoundManager>::getInstance().play(SoundType::CLICK_BUTTON);
        Singleton<Game>::getInstance().replaceState(new KeyBindingState);
     }
}

void AudioSettingsMenu::update(float deltatime) {
	backButton->update(deltatime);
	Singleton<SoundManager>::getInstance().updateMusic(deltatime);

	if (draggingMusicSlider) {
		currentmusicVolume = (GetMousePosition().x - musicSlider.x) * float(1) / musicSlider.width;
		currentmusicVolume = clamp(currentmusicVolume, 0.0f, 1.0f);
		musicSliderHandle.x = musicSlider.x + currentmusicVolume * (musicSlider.width - musicSliderHandle.width);
		Singleton<SoundManager>::getInstance().setvaluemusicVolume(currentmusicVolume);
		Singleton<SoundManager>::getInstance().setmusicVolume();
	}
	if (draggingSoundSlider) {
		currentsoundVolume = (GetMousePosition().x - soundSlider.x) * float(1) / soundSlider.width;
		currentsoundVolume = clamp(currentsoundVolume, 0.0f, 1.0f);
		soundSliderHandle.x = soundSlider.x + currentsoundVolume * (soundSlider.width - soundSliderHandle.width);
		Singleton<SoundManager>::getInstance().setvaluesoundVolume(currentsoundVolume);
		Singleton<SoundManager>::getInstance().setsoundVolume();
	}
}

void AudioSettingsMenu::render() {
	// DrawTexture(background, 0, 0, WHITE); DrawTexturePro(background,
	// 	{ 0,0, (float)background.width,(float)background.height },
	// 	{ 0,0, screenWidth, screenHeight },
	// 	{ 0,0 }, 0, WHITE);
	DrawRectangleRec(Rectangle{ 0, 0, screenWidth, screenHeight }, Fade(BLACK, 0.6f));
	backButton->draw();
	DrawTexture(audioPanel, positionPanel.x, positionPanel.y, WHITE);
	float textPosX = positionPanel.x + 200;
	DrawText(musicText, textPosX, musicSlider.y, 20, darkYellow);
	DrawText(soundText, textPosX, soundSlider.y, 20, darkYellow);
	DrawText(TextFormat("%.2f", currentmusicVolume), textPosX + LEFT_MARGIN + MeasureText(musicText, 20) + 8, musicSlider.y, 20, WHITE);
	DrawText(TextFormat("%.2f", currentsoundVolume), textPosX + LEFT_MARGIN + MeasureText(soundText, 20) + 8, soundSlider.y, 20, WHITE);
	DrawRectangleRounded(musicSlider, 0.4f, 15, DARKGRAY);
	DrawRectangleRounded(soundSlider, 0.4f, 15, DARKGRAY);
	DrawRectangleRounded({ musicSlider.x, musicSlider.y, musicSliderHandle.x - musicSlider.x, musicSlider.height }, 0.4f, 15, darkYellow);
	DrawRectangleRounded({ soundSlider.x, soundSlider.y, soundSliderHandle.x - soundSlider.x, soundSlider.height }, 0.4f, 15, darkYellow);
	DrawRectangleRounded(musicSliderHandle, 0.4f, 15, DARKBLUE);
	DrawRectangleRounded(soundSliderHandle, 0.4f, 15, DARKBLUE);
}


