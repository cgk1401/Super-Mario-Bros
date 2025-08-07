#include "CUTSCENES/ScreenEffectCutscene.h"
#include "Global.h"
ScreenEffectCutscene::ScreenEffectCutscene(SreenType _type, Color _color, float _time, string _text): type(_type), color(_color), text(_text){
    time.start(_time);
    alpha = 1;
    FONT = LoadFont("../assets/font/PolygonParty.ttf");
 }
void ScreenEffectCutscene::update(float dt){
    time.update(dt);
    if(time.isRunning()){
        if(type == SreenType::FADE_IN)
        {
            alpha = 1 - time.getProgress();
        }
        else if (type == SreenType::FADE_OUT){
            alpha = time.getProgress();
        }
    }
}
void ScreenEffectCutscene::draw() {
    Rectangle rect  = {0,0, screenWidth, screenHeight};
    DrawRectangleRec(rect, Fade(color, alpha));
     float textFontSize = 50;
    float spacing = 2;
    Vector2 textPos = MeasureTextEx(FONT, text.c_str(), textFontSize, spacing);
    
    float textX = rect.x + (rect.width - textPos.x) / 2;
    float textY = rect.y + (rect.height - textPos.y) / 2;
    DrawTextEx(FONT, text.c_str(), { textX, textY }, textFontSize, spacing, Fade(WHITE, alpha));
}

bool ScreenEffectCutscene::isFinished() const {
    return finished || time.isFinished();
}