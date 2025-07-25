#pragma once

#include "GameState.h"
#include "../headers/Global.h"

class AudioSettingsMenu : public GameState {
private :
    Texture background;
    Texture audioPanel;
    Vector2 positionPanel;

    Button* backButton;

    float musicVolume;
    float soundVolume;
public :
    AudioSettingsMenu();
    ~AudioSettingsMenu();

    void update(float deltatime) override;
    void render() override;
    bool allowUpdateBelow() override { return false; }

    void setmusicVolume(MusicType type);
    void setsoundVolume(SoundType type);
};

