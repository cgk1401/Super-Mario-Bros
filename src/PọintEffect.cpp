#include "../headers/PointEffect.h"
#include "OBSERVER/EventDataBase.h"
PointEffect::PointEffect(Vector2 position, EventType type){
    pos = position;
    event = type;
    time.start(0.8f);
}

PointEffect::~PointEffect(){
}

void PointEffect::update(float dt) {
    time.update(dt);

   if(time.isRunning()){
        pos.y -= speed * dt;
   }
}


void PointEffect::draw(const Texture2D& texture) {
    map<EventType, EventInfo> eventMap = Singleton<EventDataBase>::getInstance().getMap();
    auto it = eventMap.find(event);
    if(it != eventMap.end() && it->second.label != "")
        DrawText(it->second.label.c_str(), pos.x, pos.y, 35, Fade(WHITE, 0.8f));
}

bool PointEffect::isFinished() const {
    return time.isFinished();
}
   