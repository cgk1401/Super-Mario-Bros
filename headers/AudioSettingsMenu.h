#pragma once

#include "GameState.h"
#include "../headers/Global.h"

class AudioSettingsMenu : public GameState {
private :
    Texture background;
    Texture audioPanel;
    Vector2 positionPanel;

    Button* backButton;

    Rectangle musicSlider;
    Rectangle soundSlider;
    Rectangle musicSliderHandle;
    Rectangle soundSliderHandle;

    float currentmusicVolume;
    float currentsoundVolume;

    const char* musicText = "MUSIC";
    const char* soundText = "SOUND";
    Color darkYellow = { 204, 153, 0, 255 };
    float LEFT_MARGIN = 30;
    bool draggingMusicSlider;
    bool draggingSoundSlider;
    Rectangle keybindingButton;

    Font font;
public :
    AudioSettingsMenu();
    ~AudioSettingsMenu();

    void handleInput() override;
    void update(float deltatime) override;
    void render() override;
    bool allowUpdateBelow() override { return false; }
};

