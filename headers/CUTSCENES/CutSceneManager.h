#pragma once
#include "CUTSCENES/Cutscene.h"
#include "CUTSCENES/ScreenEffectCutscene.h"
#include "CUTSCENES/KidnapCutscene.h"
#include "CUTSCENES/FlagPoleCutscene.h"
#include <vector>
using namespace std;

class CutsceneManager {
public:
    CutsceneManager();
    ~CutsceneManager();

    void play(Cutscene* cutscene);
    void update(float dt);
    void draw();
    bool isActive() const;
private:
    Button* skip_button;
    vector<Cutscene*> cutscenes;
    Timer time;
};
