#ifndef PLAY_STATE_H
#define PLAY_STATE_H
#include <raylib.h>

#include "../headers/GameState.h"
#include "../headers/GUI.h"
#include "../headers/PauseState.h"
#include "../headers/Map.h"
#include "../headers/CameraController.h"
#include "../headers/ParallaxManager.h"
#include "../headers/GoomBa.h"
#include "../headers/KoopaTroopa.h"
#include "../headers/PiranhaPlant.h"
#include "../headers/Enemy.h"


class PlayState : public GameState{
public:
    PlayState();
    ~PlayState();
    void update(float deltatime) override;
    void render() override;

private:
    GUI gui;
    Map* map;
    Character* mario = new Mario({100, 200});
    vector<Enemy*> enemies;

    CameraController camera;
    ParallaxManager bg; //background
    ParallaxManager fg; //foreground
};

#endif