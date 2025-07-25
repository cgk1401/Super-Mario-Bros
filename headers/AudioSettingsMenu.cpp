#include "AudioSettingsMenu.h"
#include "SoundManager.h"
#include <raylib.h>

AudioSettingsMenu::AudioSettingsMenu() {
	background = resizedImage("../assets/GUI/Menu Background.png", screenWidth, screenHeight);
	audioPanel = Singleton<TextureManager>::getInstance().load(TextureType::AUDIOPANEL);

	float widthPanel = audioPanel.width;
	float heightPanel = audioPanel.height;

	positionPanel.x = (screenWidth - widthPanel) * float(1) / 2;
	positionPanel.y = (screenHeight - heightPanel) * float(1) / 2;
	backButton = new Button("../assets/GUI/back_button.png", 10, 10, 100, 100, "", WHITE);
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
}

void AudioSettingsMenu::render() {
	DrawTexture(background, 0, 0, WHITE);
	DrawRectangleRec(Rectangle{ 0, 0, screenWidth, screenHeight }, Fade(BLACK, 0.4f));
	backButton->draw();
	DrawTexture(audioPanel, positionPanel.x, positionPanel.y, WHITE);
	
}

void AudioSettingsMenu::setmusicVolume(MusicType type) {
	SetMusicVolume(Singleton<SoundManager>::getInstance().getMusic(type), musicVolume);
}

void AudioSettingsMenu::setsoundVolume(SoundType type) {
	SetSoundVolume(Singleton<SoundManager>::getInstance().getSound(type), soundVolume);
}

