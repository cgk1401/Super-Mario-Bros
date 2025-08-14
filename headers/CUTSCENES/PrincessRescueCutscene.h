#pragma once
#include "CUTSCENES/Cutscene.h"
#include <string>
#include <raylib.h>
#include "Character.h"
#include "Princess.h"
#include "CameraController.h"
#include "Map.h"
#include "HUD.h"
#include "KidnapCutscene.h"
using namespace std;

enum class PrincessRescuePhase{
    START,
    KISS,
    CLOSE1,
    OUTRO1,
    BACK_TO_KISS_SCENE,
    DISAPPEAR,
    CLOSE2,
    OUTRO2,
    DONE,
};
class PrincessRescueCutscene : public Cutscene{
public:
    PrincessRescueCutscene(Character* _player, CameraController& _camera, Princess* _princess, HUD* _hud,  Map* map);
    ~PrincessRescueCutscene() = default;
    void update(float dt) override;
    void draw() override;
    bool isFinished() const override;
    void setFinish() override;
private:
    UFOInvader ufo;
    Character* player;
    Princess* princess;
    CameraController* camera;
    Map* map;
    HUD* hud;
    string nextMap_filename;
    float elapsedTime = 0;
    PrincessRescuePhase currentPhase = PrincessRescuePhase::START;
    vector<Rectangle> blackScene;
    Font FONT;
private:
    void handlePhase(float dt);
};