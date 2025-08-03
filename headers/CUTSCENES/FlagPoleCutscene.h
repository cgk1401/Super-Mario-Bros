#pragma once
#include "CUTSCENES/Cutscene.h"
#include "Timer.h"
#include "Animation.h"
#include "Global.h"
#include "CameraController.h"
#include "Map.h"
#include <string>
#include <raylib.h>
#include <map>
using namespace std;

class HUD;

enum class FlagPolePhase{
    SLIDE_DOWN,
    WALK,
    INTO_CASTLE,
    WAIT,
    DONE,
};
class FlagPoleCutscene : public Cutscene {
public:
    FlagPoleCutscene(Character* _player, HUD* _hud, Map* _map, CameraController _camera);
    ~FlagPoleCutscene() = default;

    void update(float dt) override;
    void draw() override;
    bool isFinished() const override;

private:
    Character* player;
    HUD* hud;
    Map* map;
    CameraController camera;
    float elapsedTime = 0.0f;
    FlagPolePhase currentPhase = FlagPolePhase::SLIDE_DOWN;
private:
    void handlePhase(float dt);
};
