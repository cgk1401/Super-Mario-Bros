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
#include "../headers/Character.h"
#include "../headers/Luigi.h"
#include "../headers/Mario.h"
#include "../headers/NormalState.h"
#include "../headers/SuperState.h"

class PlayState : public GameState{
public:
    PlayState();
    ~PlayState();
    void    handleInput(Game& game) override;
    void    update(Game& game)      override;
    void    render()                override;
private:
    bool isPlaying;
    GUI gui;
    PauseState pauseMenu;
    Map* map;
    //Mario mario;
    Character* mario = new Luigi({100, 500});
    GoomBa goomba;
    KoopTroopa kooptroopa;
    PiranhaPlant piranhaPlant; 
    CameraController camera;
    ParallaxManager bg; //background
    ParallaxManager fg; //foreground
};

#endif