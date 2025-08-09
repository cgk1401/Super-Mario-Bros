#pragma once
#include "CUTSCENES/Cutscene.h"
#include "Timer.h"
#include <string>
#include <raylib.h>
using namespace std;

enum class SreenType{
    NONE,
    FADE_IN,
    FADE_OUT,
};

class ScreenEffectCutscene : public Cutscene{
public:
    ScreenEffectCutscene(SreenType _type, Color _color, float _time, string _text = "");
     ~ScreenEffectCutscene() = default;
    void update(float dt) override;
    void draw() override;
    bool isFinished() const override;
    void setFinish() override{ finished = true;}
private:
    Color color;
    SreenType type;
    Timer time;
    string text;
    float alpha;
    Font FONT;
    bool finished = false;
};