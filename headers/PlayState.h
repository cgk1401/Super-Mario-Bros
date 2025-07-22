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
    void ChangeCharacter(CharacterType newtype);

private:
    GUI gui;
    Map* map;
    Texture2D world_1_1;
    //Character* mario = new Mario({100, 200});
    Character* character;
    vector<Enemy*> enemies;

    CameraController camera;
    ParallaxManager bg; //background
    ParallaxManager fg; //foreground
};

#endif