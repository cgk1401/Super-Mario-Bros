#ifndef GUI_H
#define GUI_H
#include "raylib.h"
#include "../headers/Button.h"
#include "../headers/Mario.h"
#include "OBSERVER/Observer.h"
class Game;

class HUD : public Observer {
private:
    float time;
    int score;
    int coins;
    pair<int, int> map_level;
    int lives;
    
    Font font;
    int fontSize;
    Rectangle hudRect; //vùng giới hạn các position của các thông số trên 
   
public:
    HUD(pair<int, int> level = {1,1});
    HUD(const HUD& a) = default;
    ~HUD();
    void setScore(int s);
    void setCoins(int c);
    void setLives(int l);
    void setMapLevel(pair<int, int> m);
    void setTime(int t);
    int getLives();
    int getTime();
    void generateTimeToCoins();

    void update(float dt);
    void draw();
    void onNotify(const EventType& event, void* data = nullptr) override;
};
#endif