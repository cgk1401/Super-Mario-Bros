#include "CUTSCENES/KidnapCutscene.h"
#include "CUTSCENES/ScreenEffectCutscene.h"
#include "Global.h"
#include "cmath"
#define SCALE 5.0f
//Set states
template <typename T>
void setState(T& current,T newState){
    if(current != newState){
        current = newState;
    }
}
//____________________________PRINCESS_________________ 
Princess::Princess(){
    texture = LoadTexture("../assets/Cutscene/Kidnap/Princess Peach.png");
    Animation idle;
    idle.frame.push_back({8, 72, 24, 32});
    idle.frame.push_back({8, 72, 24, 32});
    idle.frame.push_back({8, 72, 24, 32});
    idle.frame.push_back({136, 72, 24, 32});
    idle.durationtime = 0.2;
    animation[PrincessState::IDLE] = idle;

    Animation walk;
    walk.frame.push_back({72, 72, 24, 32});
    walk.frame.push_back({104, 72, 24, 32});
    walk.durationtime = 0.1f;
    animation[PrincessState::WALK] = walk;

    Animation kidnap;
    for(int i = 0; i < 4; i++){
        kidnap.frame.push_back({8 + (float) 32 * i, 24, 24 , 24});
    }
    kidnap.durationtime = 0.1f;
    animation[PrincessState::KIDNAP] = kidnap;

    Animation disappear;
    for(int i = 0; i < 4; i++){
        disappear.frame.push_back({8 + (float) 32 * i, 24, 24 , 24});
        disappear.frame.push_back({263, 72, 24, 24});
    }
    disappear.durationtime = 0.05f;
    animation[PrincessState::DISAPPEAR] = disappear;

    position = {500, 600};
    currentState = PrincessState::IDLE;
}
void Princess::moveLeft(){
    direction = Direction::Left;
    setState(currentState, PrincessState::WALK);
    position.x += -speed;
}

void Princess::moveRight(){
    direction = Direction::Right;
    setState(currentState, PrincessState::WALK);
    position.x += speed;
}

void Princess::update(float dt){
    animation.at(currentState).Update(dt);
}
void Princess::draw(){
    Rectangle currentframe = animation[currentState].getcurrentframe();
	
	if (direction == Direction::Right) {
		currentframe.width = -abs(currentframe.width);
	}
	else if (direction == Direction::Left) {
		currentframe.width = abs(currentframe.width);
	}

	Rectangle destination = { position.x, position.y, currentframe.width * SCALE, currentframe.height * SCALE };
    bound = destination;
	DrawTexturePro(texture, currentframe, destination, { 0,0 }, 0, WHITE);
}


//_________________________UFO_______________________

UFOInvader::UFOInvader(){
    texture = LoadTexture("../assets/Cutscene/Kidnap/UFO Invader.png");

    Animation fly;
    for(int i = 0; i < 1; i++){
        for(int j = 0; j < 6; j++){
            fly.frame.push_back({6 + (float) j * 50, 13 + (float)i * 71, 50, 71});
        }
    }
    fly.durationtime = 0.08f;
    animation[UFOState::FLY] = fly;

    Animation appear;
    for(int i = 0; i < 13;i++){
        appear.frame.push_back({-1 + (float) 50 * i, 630, 50, 71});
    }
    appear.durationtime = 0.05f;
    appear.loop = false;
    animation[UFOState::APPEAR] = appear;

    Animation disappear;
    for(int i = 12; i >= 0;i--){
        disappear.frame.push_back({-1 + (float) 50 * i, 630, 50, 71});
    }
    disappear.durationtime = 0.05f;
    disappear.loop = false;
    animation[UFOState::DISAPPEAR] = disappear;

    position = {500, 600};
    currentState = UFOState::FLY; 
}

void UFOInvader::update(float dt){
    animation.at(currentState).Update(dt);
}
void UFOInvader::draw(){
    Rectangle currentframe = animation.at(currentState).getcurrentframe();
	
	if (direction == Direction::Right) {
		currentframe.width = abs(currentframe.width);
	}
	else if (direction == Direction::Left) {
		currentframe.width = -abs(currentframe.width);
	}

	Rectangle destination = { position.x, position.y, currentframe.width * SCALE, currentframe.height * SCALE };

	DrawTexturePro(texture, currentframe, destination, { 0,0 }, 0, WHITE);
}


//_______________________Kidnap Cutscene_________________________
KidnapCutscene::KidnapCutscene(){
    princess.position = {500, 680};
    ufo.position = {550, 470};
    camera.init({0,0});
    map = new Map({1,1});
    map->loadFromFile({1,1});

    for(int i = 0; i < 4; i++) help_Ani.frame.push_back({136 +(float) i * 40, 24, 32, 16});
    help_Ani.durationtime = 0.1f;

    blackScene.resize(2);
    blackScene[0] = {-1, -screenHeight - 1, screenWidth, screenHeight};
    blackScene[1] = {0, screenHeight + 1, screenWidth, screenHeight};
    start = false;
}
void KidnapCutscene::handlePhase(float dt) {
    switch (currentPhase) {
        case KidnapPhase::INTRO:
            princess.moveRight();
            if (elapsedTime > 3.0f) {
                currentPhase = KidnapPhase::WALKING;
                
            }
            break;
        case KidnapPhase::WALKING:
            princess.moveRight();
            if (elapsedTime > 5.0f) {
                Singleton<SoundManager>::getInstance().play(SoundType::TELEPORT);
                ufo.currentState = UFOState::APPEAR;
                currentPhase = KidnapPhase::UFO_APPEARS;
            }
            break;

        case KidnapPhase::UFO_APPEARS:
               Vector2 targetPos;
                targetPos.x = princess.position.x - 300;
                targetPos.y = princess.position.y - 150;

                camera.getCamera().target.x = lerp(camera.getCamera().target.x, targetPos.x, dt * 3);
                camera.getCamera().target.y = lerp(camera.getCamera().target.y, targetPos.y, dt * 3);
                camera.getCamera().zoom     = lerp(camera.getCamera().zoom, 2.0f, dt * 3);

                blackScene[0].y = lerp(blackScene[0].y, -screenHeight + 200, dt * 3);
                blackScene[1].y = lerp(blackScene[1].y, 550, dt * 3);
            if (ufo.animation.at(ufo.currentState).isFinish()) {
                Singleton<SoundManager>::getInstance().play(SoundType::SCREAM);
                ufo.currentState = UFOState::FLY;
                currentPhase = KidnapPhase::HELP;
            }
            break;

        case KidnapPhase::HELP:
            help_Ani.Update(dt);
           princess.currentState = PrincessState::KIDNAP;
           if(elapsedTime > 8.0f){
                Singleton<SoundManager>::getInstance().play(SoundType::TELEPORT);
            princess.currentState = PrincessState::DISAPPEAR;
            ufo.currentState = UFOState::DISAPPEAR;
            currentPhase = KidnapPhase::DISAPPEAR;
           }
            break;

        case KidnapPhase::DISAPPEAR:
            if (ufo.animation.at(ufo.currentState).isFinish()) {
                currentPhase = KidnapPhase::WAIT;
            }
            break;
        case KidnapPhase::WAIT: {   
            Vector2 targetPos;
            targetPos.x = 0;
            targetPos.y = 0;

            camera.getCamera().target.x = lerp(camera.getCamera().target.x, 0, dt *  3);
            camera.getCamera().target.y = lerp(camera.getCamera().target.y, 0, dt * 3);
            camera.getCamera().zoom     = lerp(camera.getCamera().zoom, 1, dt * 4);
               blackScene[0].y = lerp(blackScene[0].y, -screenHeight - 1, dt * 3);
                blackScene[1].y = lerp(blackScene[1].y, screenHeight + 1, dt * 3);
            if(elapsedTime > 11.0f){
                currentPhase = KidnapPhase::DONE;
            }
            break;
        }
        case KidnapPhase::DONE:
            break;
    }
}

void KidnapCutscene::update(float dt) {
    if (!start) {
        Singleton<SoundManager>::getInstance().play(SoundType::FOOTSTEP);
    }
    start = true;

    elapsedTime += dt;
    handlePhase(dt);

    princess.update(dt);
    ufo.update(dt);
    //camera.update(princess.bound, screenWidth * 3);
    map->update();

    
}

void KidnapCutscene::draw(){
    BeginMode2D(camera.getCamera());
    map->draw();
    if(currentPhase != KidnapPhase::WAIT){
        
        if(currentPhase == KidnapPhase::UFO_APPEARS || currentPhase ==KidnapPhase::HELP || currentPhase == KidnapPhase::DISAPPEAR){
            ufo.draw();
        }
        princess.draw();
    }
     EndMode2D();

    for(auto& rect: blackScene){
        DrawRectangleRec(rect, BLACK);
    }
    if(currentPhase == KidnapPhase::HELP){
        DrawTexturePro(princess.texture,
                    help_Ani.getcurrentframe(),
                    {850, 150, 400, 200}, 
                    {0,0},
                    0,
                    WHITE);
    }

    
    if(currentPhase == KidnapPhase::INTRO){
        Rectangle rect = {0,0, screenWidth, screenHeight};
        DrawRectangleRec(rect, Fade(BLACK,1 - (elapsedTime / 3)));
    }
}
bool KidnapCutscene::isFinished() const{
    return currentPhase == KidnapPhase::DONE;
}