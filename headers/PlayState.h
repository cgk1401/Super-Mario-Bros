#ifndef PLAY_STATE_H
#define PLAY_STATE_H
#include <raylib.h>
#include <map>

#include "../headers/GameState.h"
#include "../headers/HUD.h"
#include "../headers/PauseState.h"
#include "../headers/Map.h"
#include "../headers/CameraController.h"
#include "../headers/ParallaxManager.h"
#include "../headers/GoomBa.h"
#include "../headers/KoopaTroopa.h"
#include "../headers/PiranhaPlant.h"
#include "../headers/Enemy.h"
using namespace std;

class PlayState : public GameState{
public:
    PlayState(pair<int, int> _level = {1,1});

    ~PlayState();
    void update(float deltatime) override;
    void render() override;
    void ChangeCharacter(CharacterType newtype);


private:
    HUD hud;
    //Map* map;
    //Manage the level for each world
    std::map<pair<int, int>, Map*> world; //world[1][1] -> level 1-1'
    pair<int, int> level = {1, 1};

    //Character* mario = new Mario({100, 200});
    Character* character;
    vector<Enemy*> enemies;
    
    CameraController camera;
    ParallaxManager bg; //background
    ParallaxManager fg; //foreground

    Button* PauseButton;
};

#endif