#include "CUTSCENES/PrincessRescueCutscene.h"
#include "LevelCompleteState.h" 
#include "TextureManager.h"
#include "Global.h"
PrincessRescueCutscene::PrincessRescueCutscene(Character* _player, CameraController& _camera, Princess* _princess, HUD* _hud, Map* _map){
   player = _player;
   player->velocity = {0,0};
   map = _map;
   hud = _hud;
   princess = _princess;
   camera = &_camera;
   player->isControlled = true;
   //Singleton<SoundManager>::getInstance().play(SoundType::PIPEDOWN);
   blackScene.resize(2);
   blackScene[0] = {-screenWidth,0, screenWidth, screenHeight};
   blackScene[1] = {screenWidth, 0, screenWidth, screenHeight};
   FONT = Singleton<TextureManager>::getInstance().load(MyFontType::POLYGON_PARTY);
   Singleton<SoundManager>::getInstance().playMusic(MusicType::CASTLE_DANCE, false);
    ufo.position = {princess->position.x - 50, princess->position.y - 150};
    ufo.direction = Direction::Right;
 }

void PrincessRescueCutscene::handlePhase(float dt) {
    switch (currentPhase)
    {
    case PrincessRescuePhase::START:
        princess->currentState == PrincessState::IDLE;
        player->setActionState(ActionState::Idle);
        Vector2 targetPos;
        targetPos.x = princess->position.x - 300;
        targetPos.y = princess->position.y - 150;

        camera->getCamera().target.x = lerp(camera->getCamera().target.x, targetPos.x, dt);
        camera->getCamera().target.y = lerp(camera->getCamera().target.y, targetPos.y, dt);
        camera->getCamera().zoom     = lerp(camera->getCamera().zoom, 2.0f, dt);
        blackScene[0].x = lerp(blackScene[0].x, -screenWidth + 300, dt * 2 );
        blackScene[1].x = lerp(blackScene[1].x, screenWidth - 300, dt * 2 );
        if(elapsedTime > 2){
            elapsedTime = 0;
            currentPhase = PrincessRescuePhase::KISS;
            Singleton<SoundManager>::getInstance().play(SoundType::PRINCESS_KISS);
            princess->kiss();
        }
        break;
    case PrincessRescuePhase::KISS:
        blackScene[0].x = lerp(blackScene[0].x, -screenWidth + 250, dt * 2);
        blackScene[1].x = lerp(blackScene[1].x, screenWidth - 350, dt * 2);
        if(elapsedTime > 2){
            elapsedTime = 0;
            currentPhase = PrincessRescuePhase::CLOSE1;
        }
        break;
    case PrincessRescuePhase::CLOSE1:
        blackScene[0].x = lerp(blackScene[0].x, -screenWidth / 2, dt * 4);
        blackScene[1].x = lerp(blackScene[1].x, screenWidth / 2, dt * 4);
        if(elapsedTime > 3){
            elapsedTime = 0;
            currentPhase = PrincessRescuePhase::OUTRO1;
        }
        break;
    case PrincessRescuePhase::OUTRO1:
        if(elapsedTime > 5){
            princess->currentState = PrincessState::IDLE;
            Singleton<SoundManager>::getInstance().play(SoundType::FAR_BOOM);
            elapsedTime = 0;
            currentPhase = PrincessRescuePhase::BACK_TO_KISS_SCENE;
             Singleton<SoundManager>::getInstance().stopMusic();
        }
        break;
    case PrincessRescuePhase::BACK_TO_KISS_SCENE:
        blackScene[0].x = lerp(blackScene[0].x, -screenWidth + 250, dt * 5);
        blackScene[1].x = lerp(blackScene[1].x, screenWidth - 350, dt * 5);
        if(elapsedTime > 2){
            elapsedTime = 0;
            Singleton<SoundManager>::getInstance().play(SoundType::DRAMATIC_CINEMA_GLITCH);
            princess->currentState = PrincessState::INDLE_DISAPPEAR;
            currentPhase = PrincessRescuePhase::DISAPPEAR;
        }
        break;
    case PrincessRescuePhase::DISAPPEAR:
        ufo.update(dt);
        if(elapsedTime > 0.5f)
            ufo.currentState = UFOState::APPEAR;
        if(elapsedTime > 0.7f){
            princess->currentState = PrincessState::INVISIBLE;
        }
        if(elapsedTime > 2)
        {
            elapsedTime = 0;
            Singleton<SoundManager>::getInstance().play(SoundType::WHOOSH);
            currentPhase = PrincessRescuePhase::CLOSE2;
        }
        break;
    case PrincessRescuePhase::CLOSE2:
        blackScene[0].x = lerp(blackScene[0].x, -screenWidth / 2, dt * 10);
        blackScene[1].x = lerp(blackScene[1].x, screenWidth / 2, dt * 10);
        if(elapsedTime > 3){
            elapsedTime = 0;
             Singleton<SoundManager>::getInstance().continueMusic();
            currentPhase = PrincessRescuePhase::OUTRO2;
        }
        break;
    case PrincessRescuePhase::OUTRO2:
        if(elapsedTime > 5){
            elapsedTime = 0;
            currentPhase = PrincessRescuePhase::DONE;
        }
        break;
    default:
        break;
    }
}
void PrincessRescueCutscene::update(float dt){
   Singleton<SoundManager>::getInstance().updateMusic(dt);
    elapsedTime += dt;
    Collision::handleMapCollision(player, map);
    handlePhase(dt);
    player->update(dt);
    princess->update(dt);


}
void PrincessRescueCutscene::draw() {
    if(currentPhase >= PrincessRescuePhase::DISAPPEAR){
        BeginMode2D(camera->getCamera());
        if(currentPhase == PrincessRescuePhase::DISAPPEAR && elapsedTime < 0.5f){

        }
        else ufo.draw();
        EndMode2D();
    }
   for(auto& rect: this->blackScene){
        DrawRectangleRec(rect, BLACK);
   }

   if(currentPhase == PrincessRescuePhase::OUTRO1){
    if(elapsedTime < 3)
        DrawTextEx(FONT, "Princess Saved",{ screenWidth / 2- 200, screenHeight / 2}, 50, 5, WHITE);
    else if(elapsedTime < 5){
         DrawTextEx(FONT, "But your adventure is not over...", { screenWidth / 2 - 350, screenHeight / 2 }, 40, 5, WHITE);
    }
   }
   else if (currentPhase == PrincessRescuePhase::OUTRO2)
        DrawTextEx(FONT, "Thanks for playing!", { screenWidth / 2 - 250, screenHeight / 2 }, 50, 5, WHITE);
   
}

void PrincessRescueCutscene::setFinish() {
    currentPhase = PrincessRescuePhase::DONE;
}

bool PrincessRescueCutscene::isFinished() const {
    if(currentPhase == PrincessRescuePhase::DONE){
        player->isControlled = false;
        Singleton<Game>::getInstance().addState(new LevelCompleteState(hud, player, map));

    }
    return currentPhase == PrincessRescuePhase::DONE;
}