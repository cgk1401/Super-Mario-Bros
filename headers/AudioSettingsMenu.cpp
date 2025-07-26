#include "AudioSettingsMenu.h"
#include "SoundManager.h"
#include <raylib.h>
#include <algorithm>
#include <cstdio>

AudioSettingsMenu::AudioSettingsMenu() {
	background = resizedImage("../assets/GUI/Menu Background.png", screenWidth, screenHeight);
	audioPanel = Singleton<TextureManager>::getInstance().load(TextureType::AUDIOPANEL);

	float widthPanel = audioPanel.width;
	float heightPanel = audioPanel.height;

	positionPanel.x = (screenWidth - widthPanel) * float(1) / 2;
	positionPanel.y = (screenHeight - heightPanel) * float(1) / 2;
	backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);

	float widthslider = 400;
	float heightslider = 20;
	float widthText = MeasureText(musicText, 20);
	musicVolume = 0.5;
	soundVolume = 0.5;

	float spacingX = (widthPanel - widthslider - LEFT_MARGIN - widthText) * float(1) / 2;
	float spacingY = (heightPanel - heightslider * 2) * float(1) / 3;
	musicSlider = { positionPanel.x + LEFT_MARGIN + widthText + spacingX, positionPanel.y + spacingY, widthslider, heightslider };
	soundSlider = { positionPanel.x + LEFT_MARGIN + widthText + spacingX, positionPanel.y + spacingY * 2 + heightslider, widthslider, heightslider };
	musicSliderHandle = { musicSlider.x + widthslider * musicVolume, musicSlider.y - 10, 10, 40 };
	soundSliderHandle = { soundSlider.x + widthslider * soundVolume, soundSlider.y - 10, 10, 40 };
	draggingMusicSlider = false;
	draggingSoundSlider = false;
}

AudioSettingsMenu::~AudioSettingsMenu() {
	delete backButton;
	UnloadTexture(background);
}

void AudioSettingsMenu::update(float deltatime) {
	backButton->update(deltatime);

	if (backButton->IsClicked()) {
		Singleton<Game>::getInstance().pop();
	}

	if (CheckCollisionPointRec(GetMousePosition(), musicSliderHandle) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		draggingMusicSlider = true;
	}
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		draggingMusicSlider = false;
	}

	if (draggingMusicSlider) {
		musicVolume = (GetMousePosition().x - musicSlider.x) * float(1) / musicSlider.width;
		musicVolume = clamp(musicVolume, 0.0f, 1.0f);
		musicSliderHandle.x = musicSlider.x + musicVolume * (musicSlider.width - musicSliderHandle.width);
	}

	if (CheckCollisionPointRec(GetMousePosition(), soundSliderHandle) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		draggingSoundSlider = true;
	}
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		draggingSoundSlider = false;
	}

	if (draggingSoundSlider) {
		soundVolume = (GetMousePosition().x - soundSlider.x) * float(1) / soundSlider.width;
		soundVolume = clamp(soundVolume, 0.0f, 1.0f);
		soundSliderHandle.x = soundSlider.x + soundVolume * (soundSlider.width - soundSliderHandle.width);
	}
}

void AudioSettingsMenu::render() {
	DrawTexture(background, 0, 0, WHITE);
	DrawRectangleRec(Rectangle{ 0, 0, screenWidth, screenHeight }, Fade(BLACK, 0.4f));
	backButton->draw();
	DrawTexture(audioPanel, positionPanel.x, positionPanel.y, WHITE);
	DrawText(musicText, positionPanel.x + LEFT_MARGIN, musicSlider.y, 20, darkYellow);
	DrawText(soundText, positionPanel.x + LEFT_MARGIN, soundSlider.y, 20, darkYellow);
	DrawText(TextFormat("%.2f", musicVolume), positionPanel.x + LEFT_MARGIN + MeasureText(musicText, 20) + 8, musicSlider.y, 20, WHITE);
	DrawText(TextFormat("%.2f", soundVolume), positionPanel.x + LEFT_MARGIN + MeasureText(soundText, 20) + 8, soundSlider.y, 20, WHITE);
	DrawRectangleRounded(musicSlider, 0.4, 15, darkYellow);
	DrawRectangleRounded(soundSlider, 0.4, 15, darkYellow);
	DrawRectangleRounded(musicSliderHandle, 0.4, 15, DARKGRAY);
	DrawRectangleRounded(soundSliderHandle, 0.4, 15, DARKGRAY);
}

void AudioSettingsMenu::setmusicVolume(MusicType type) {
	SetMusicVolume(Singleton<SoundManager>::getInstance().getMusic(type), musicVolume);
}

void AudioSettingsMenu::setsoundVolume(SoundType type) {
	SetSoundVolume(Singleton<SoundManager>::getInstance().getSound(type), soundVolume);
}

