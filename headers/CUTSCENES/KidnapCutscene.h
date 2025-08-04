#pragma once
#include "CUTSCENES/Cutscene.h"
#include "Timer.h"
#include "Animation.h"
#include "Global.h"
#include "CameraController.h"
#include "Map.h"
#include <string>
#include <raylib.h>
#include <map>
using namespace std;

//_______________PRINCESS_________________ 
enum class PrincessState{
    IDLE,
    KIDNAP,
    WALK,
    RUN,
    DISAPPEAR,
};
class Princess {
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
    Princess();
    void update(float dt);
    void draw();
    void moveLeft();
    void moveRight();
};

//________________UFO_______________________
enum class UFOState{
    APPEAR,
    DISAPPEAR,
    FLY,
};
class UFOInvader {
    friend class KidnapCutscene;
private: 
    Texture2D texture;
    map<UFOState, Animation> animation;
    Vector2 position;
    UFOState currentState;
    Direction direction;
public:
    UFOInvader();
    void update(float dt);
    void draw();

    void moveLeft();
};

//__________________Kidnap Cutscene__________________
enum class KidnapPhase {
    INTRO,   
    WALKING,    
    UFO_APPEARS,
    HELP,    
    DISAPPEAR,
    WAIT,
    MOVE_CAMERA_TO_MARIO,
    SURPRISED_EMOJI,
    BACK_TO_ORIGIN,
    DONE ,     
};
class KidnapCutscene : public Cutscene {
public:
    KidnapCutscene(Map* _map, Character* _character);
    ~KidnapCutscene() = default;

    void update(float dt) override;
    void draw() override;
    bool isFinished() const override;

private:
    ///Texture2D background;
    Texture2D emojiTexture; 
    bool done = false;
    float elapsedTime = 0.0f;
    KidnapPhase currentPhase = KidnapPhase::INTRO;

    Princess princess;
    UFOInvader ufo;
    CameraController camera;
    Animation help_Ani;
    Animation surprise_emoji_Ani;
    Map* map;
    Character* character;

    vector<Rectangle> blackScene;
    bool start;

    bool princess_Disappreared;

private:
    void handlePhase(float dt);

};
