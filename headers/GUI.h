#ifndef GUI_H
#define GUI_H
#include "raylib.h"
#include "../headers/Button.h"
#include "../headers/Mario.h"

class Game;

class GUI {
private:
    float time;
    int score;
    int coins;
    int map_level;
    int lives;
    Button* PauseButton;
    Font font;
    int fontSize;
    Rectangle hudRect; //vùng giới hạn các position của các thông số trên 
   
public:
    GUI();
    ~GUI();
    void setScore(int s);
    void setCoins(int c);
    void setLives(int l);
    void setMapLevel(int m);
    void setTime(int t);
    bool PauseButton_IsPressed();

    void update();
    void draw();
};
#endif