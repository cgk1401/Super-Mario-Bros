#include "CUTSCENES/FlagPoleCutscene.h"
#include "PlayState.h"
#include "HUD.h"
#include "LevelCompleteState.h"

class PlayState;
FlagPoleCutscene::FlagPoleCutscene(Character* _player, HUD* _hud, Map* _map, CameraController _camera){
    player = _player;
    player->isControlled = true;
    hud = _hud;
    map = _map;
    camera = _camera;

    Singleton<SoundManager>::getInstance().play(SoundType::FLAGPOLE);
    Singleton<SoundManager>::getInstance().playMusic(MusicType::LEVEL_COMPLETE, false);
}

void FlagPoleCutscene::handlePhase(float dt){
    switch (currentPhase)
    {
    case FlagPolePhase::SLIDE_DOWN :
        player->moveDown(5);
        player->setActionState(ActionState::FlagpoleHold);   

        if(elapsedTime > 2.0f){
            elapsedTime = 0;
            currentPhase = FlagPolePhase::WALK;
        }
        break;
    case FlagPolePhase::WALK: {
        const float speed = 2;
        player->moveRight(speed);
        Singleton<SoundManager>::getInstance().updateMusic(dt);
       if(elapsedTime > 3.1f){
            player->setActionState(ActionState::Idle);
            currentPhase = FlagPolePhase::INTO_CASTLE;
       }
        break;
    }
    case FlagPolePhase::INTO_CASTLE:
    Singleton<SoundManager>::getInstance().updateMusic(dt);
        hud->generateTimeToCoins();
        if(hud->getTime() <= 0 ){
            elapsedTime = 0;
            currentPhase = FlagPolePhase::WAIT;
        }
        break;
    case FlagPolePhase::WAIT:
        if(elapsedTime > 2){
            currentPhase = FlagPolePhase::DONE;
        }
        break;
    case FlagPolePhase::DONE:
        break;
    default:
        break;
    }

}

void FlagPoleCutscene::update(float dt) {
    elapsedTime += dt;
    Collision::handleMapCollision(player, map);
    handlePhase(dt);

    if(currentPhase != FlagPolePhase::INTO_CASTLE){
        player->update(dt);
    }
    else hud->update(dt);
}
void FlagPoleCutscene::draw() {

}
bool FlagPoleCutscene::isFinished() const {
    /*if done, move to next level*/
    if(currentPhase == FlagPolePhase::DONE){
        hud->setScore( hud->getScore() + hud->getTime() * 100);
        player->isControlled = false;
        pair<int, int> currentLevel = map->getLevel();
        pair<int, int> newLevel = {currentLevel.first, currentLevel.second + 1};
        if (newLevel.second <= 4) {
            player->notify(EventType::FINISH_LEVEL);
            Singleton<Game>::getInstance().addState(new LevelCompleteState(hud, player, map));
        }
    }
    return currentPhase == FlagPolePhase::DONE;
}
void FlagPoleCutscene::setFinish(){
currentPhase = FlagPolePhase::DONE;
}
