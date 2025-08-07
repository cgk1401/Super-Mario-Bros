#include "CUTSCENES/PipeCutscene.h"
#include "PlayState.h"
#include "Global.h"
PipeCutscene::PipeCutscene(Character* _player, HUD* _hud, Map* _map, const char* _nextMap_filename){
   player = _player;
   map = _map;
   nextMap_filename = _nextMap_filename;
   hud = _hud;
   player->isControlled = true;
   Singleton<SoundManager>::getInstance().play(SoundType::PIPEDOWN);
 }

void PipeCutscene::handlePhase(float dt) {
    switch (currentPhase)
    {
    case PipePhase::ENTER:
        player->moveRight();
        player->setActionState(ActionState::Idle);
        if(elapsedTime > 2){
            elapsedTime = 0;
            currentPhase = PipePhase::DONE;
        }
        break;
    default:
        break;
    }
}
void PipeCutscene::update(float dt){
    elapsedTime += dt;
    handlePhase(dt);
}
void PipeCutscene::draw() {
   
}

void PipeCutscene::setFinish() {
    currentPhase = PipePhase::DONE;
}

bool PipeCutscene::isFinished() const {
    if(currentPhase == PipePhase::DONE){
        player->isControlled = false;
        player->velocity = {0,0};
        Singleton<Game>::getInstance().changeState(new PlayState( map->getLevel(), hud, player, nextMap_filename.c_str()));
    }
    return currentPhase == PipePhase::DONE;
}