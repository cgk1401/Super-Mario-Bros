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
#include "../headers/FireBar.h"
#include "CUTSCENES/CutSceneManager.h"
#include "Lift.h"
#include "VerticalLift.h"
#include "Horizontal.h"
#include "Princess.h"
using namespace std;

class PlayState : public GameState, public Observer{
public:
    PlayState(pair<int, int> _level = {1,1}, HUD* hud = nullptr, Character* _character = nullptr, const char* _extraMap_filename = nullptr);
    PlayState(const char* filename);
    ~PlayState();
    void handleInput() override;
    void update(float deltatime) override;
    void render() override;
    bool allowUpdateBelow() override {return false;}
    void ChangeCharacter(CharacterType newtype);

    void onNotify(const EventType& event, void* data = nullptr) override;
    void saveGame(const char* filename);

private:
    HUD* hud;
    map<pair<int, int>, Map*> world;
    pair<int, int> level = {1, 1};

    Character* character;
    Princess* princess = nullptr;
    vector<Enemy*> enemies;
    
    CameraController camera;
    ParallaxManager bg; //background
    ParallaxManager fg; //foreground

    Button* PauseButton;

    Timer newRound_countDown;

    CutsceneManager cutscene;
    void loadGame(const char* filename);
    
};

#endif