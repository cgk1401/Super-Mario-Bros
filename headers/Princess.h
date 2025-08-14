#pragma once
#include "Animation.h"
#include "Global.h"
#include <string>
#include <raylib.h>
#include <map>

enum class PrincessState{
    IDLE,
    KIDNAP,
    WALK,
    RUN,
    DISAPPEAR,
    INDLE_DISAPPEAR,
    KISS,
    SALUTE,
    INVISIBLE,
};
class Princess  {
    friend class PrincessRescueCutscene;
    friend class KidnapCutscene;
private: 
    Texture2D texture;
    map<PrincessState, Animation> animation;
    PrincessState currentState;
    Vector2 position;
    Rectangle bound;
    Direction direction;
    float speed = 1;

public:
    Princess(Vector2 _position = {500, 600});
    void update(float dt);
    void draw();
    void moveLeft();
    void moveRight();
    void kiss();
    void salute();
    Rectangle getBound() const;
};