#include "CUTSCENES/FlagPoleCutscene.h"
#include "PlayState.h"
#include "HUD.h"

class PlayState;
FlagPoleCutscene::FlagPoleCutscene(Character* _player, HUD* _hud, Map* _map, CameraController _camera){
    player = _player;
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
            currentPhase = FlagPolePhase::WALK;
        }
        break;
    case FlagPolePhase::WALK: {
        player->moveRight();
        Singleton<SoundManager>::getInstance().updateMusic();
        Tile tile = map->getTile((player->getBound().y + player->getBound().height * 0.7f)/ Map::TILE_SIZE, (player->getBound().x ) / Map::TILE_SIZE, LayerType::PLATFORM);
        if (tile.type == TileType::BLACK_BLOCK) {
            currentPhase = FlagPolePhase::INTO_CASTLE;
        }
        break;
    }
    case FlagPolePhase::INTO_CASTLE:
    Singleton<SoundManager>::getInstance().updateMusic();
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
    Collision::handlePlayerCollision(player, map, true);
    handlePhase(dt);

    if(currentPhase != FlagPolePhase::INTO_CASTLE){
        if(currentPhase == FlagPolePhase::SLIDE_DOWN) player->Update(dt, false);
        else player->Update(dt);
    }
    else hud->update(dt);
}
void FlagPoleCutscene::draw() {

}
bool FlagPoleCutscene::isFinished() const {
    /*if done, move to next level*/
    if(currentPhase == FlagPolePhase::DONE){
        pair<int, int> currentLevel = map->getLevel();
        pair<int, int> newLevel = {currentLevel.first, currentLevel.second + 1};
        if (newLevel.second <= 4) {
            player->notify(EventType::FINISH_LEVEL);
            Singleton<Game>::getInstance().changeState(new PlayState(newLevel, hud, player));
        }
    }
    return currentPhase == FlagPolePhase::DONE;
}