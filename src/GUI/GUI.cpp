#include "GUI/GUI.h"
#include "GAME/Global.h"

GUI::GUI(){
    init();
}

void GUI::setScore(int s){
    this->score = s;
}

void GUI::setCoins(int c){
    this->coin = c;
}
void GUI::setLives(int l){
    this->lives = l;
}
void GUI::setMapLevel(int m){
    this->map_level = m;
}
void GUI::setTime(int t){
    this->time = t;
}
void GUI::init(){
    hudRect = Rectangle{0, 0,  0.2f * screenHeight, screenWidth};
}
void GUI::draw(){
    DrawRectangleRec(hudRect, RED);
}