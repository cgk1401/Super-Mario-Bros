#ifndef PLAY_STATE_H
#define PLAY_STATE_H
#include <raylib.h>

#include "../headers/GameState.h"
#include "../headers/GUI.h"
#include "../headers/PauseState.h"
#include "../headers/Map.h"
#include "../headers/CameraController.h"
#include "../headers/ParallaxManager.h"
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
    Mario mario;
    CameraController camera;
    ParallaxManager bg; //background
    

};

#endif