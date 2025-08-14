#include "Princess.h"
#define SCALE 4.5f

template <typename T>
void setState(T& current,T newState){
    if(current != newState){
        current = newState;
    }
}

Princess::Princess(Vector2 _position ){
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

    Animation kiss;
    kiss.frame.push_back({40, 128, 24, 32});
    kiss.durationtime = 1;
    animation[PrincessState::KISS] = kiss;
    
    Animation salute;
    salute.frame.push_back({72, 128,24, 32});
    salute.frame.push_back({104, 128,24, 32});
    salute.durationtime = 0.2f;
    animation[PrincessState::SALUTE] = salute;

    Animation idle_disapprear;
    idle_disapprear.frame.push_back({8, 72, 24, 32});
    idle_disapprear.frame.push_back({263, 72, 24, 24});
    idle_disapprear.durationtime = 0.05f;
    animation[PrincessState::INDLE_DISAPPEAR] = idle_disapprear;

    Animation invisible;
    invisible.frame.push_back({263, 72, 24, 24});
    invisible.durationtime = 1;
    animation[PrincessState::INVISIBLE] = invisible;

    position = _position;
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

void Princess::kiss(){
    setState(currentState, PrincessState::KISS);
}

void Princess::salute(){
    setState(currentState, PrincessState::SALUTE);
}

Rectangle Princess::getBound() const{
    const Rectangle frame = animation.at(currentState).getcurrentframe();
	float delta = frame.width *SCALE* 0.25f; //narrow the width of player
    return {
        position.x + delta,
        0,
        frame.width * SCALE - delta * 2,
        screenHeight
    };
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
