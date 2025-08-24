#pragma once
#include "CUTSCENES/Cutscene.h"
#include "Timer.h"
#include <string>
#include <raylib.h>
#include "Character.h"
#include "Map.h"
#include "HUD.h"
using namespace std;

enum class PipePhase
{
    ENTER,
    DONE,
};
class PipeCutscene : public Cutscene
{
public:
    PipeCutscene(Character *_player, HUD *_hud, Map *map, const char *_nextMap_filename);
    ~PipeCutscene() = default;
    void update(float dt) override;
    void draw() override;
    bool isFinished() const override;
    void setFinish() override;

private:
    Character *player;
    Map *map;
    HUD *hud;
    string nextMap_filename;
    float elapsedTime = 0;
    PipePhase currentPhase = PipePhase::ENTER;

private:
    void handlePhase(float dt);
};