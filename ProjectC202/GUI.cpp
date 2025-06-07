#include "GUI.h"
#include "Global.h"
#include "MenuState.h"
#include <string>
using namespace std;

GUI::GUI(){
  
}

void GUI::setScore(int s){
    this->score = s;
}

void GUI::setCoins(int c){
    this->coins = c;
}
void GUI::setLives(int l){
    this->lives = l;
}
void GUI::setMapLevel(int m){
    this->map = m;
}
void GUI::setTime(int t){
    this->time = t;
}
void GUI::init(){
    coins = 0;
    time = 60.5;
    score = 0;
    map = 1;
    lives = 3;
    hudRect = Rectangle{0, 0,  screenWidth, 0.2f * screenHeight};
    fontSize = 40;
    PauseButton = Button(hudRect.x + 10, hudRect.y + hudRect.height * 0.2f, 100, 50, "||", RED, BLUE, GREEN);
}
bool GUI::PauseButton_IsPressed(){
    return PauseButton.IsClicked();
}
void GUI::update(Game& game){
    PauseButton.update();
    if(PauseButton.IsClicked()){
        game.changeState(new MenuState());
    }
    if(time > 0) time -= GetFrameTime();
    else {
        time = 0;
        //Time out => Out Game => Display this menu: Restart + Menu
    }
    
}
void GUI::draw(){
    DrawText(TextFormat("Score\n %d", score), hudRect.x + hudRect.width * 0.2f, hudRect.y + hudRect.height * 0.1f, fontSize, BLACK );
    DrawText(TextFormat("Coins\n %d", coins), hudRect.x + hudRect.width * 0.35f, hudRect.y + hudRect.height * 0.1f, fontSize, BLACK );
    DrawText(TextFormat("Map\n %d", map), hudRect.x + hudRect.width * 0.5f, hudRect.y + hudRect.height * 0.1f, fontSize, BLACK );
    DrawText(TextFormat("Time\n %d", (int)time), hudRect.x + hudRect.width * 0.65f, hudRect.y + hudRect.height * 0.1f, fontSize, BLACK );
    DrawText(TextFormat("Lives\n %d", lives), hudRect.x + hudRect.width * 0.8f, hudRect.y + hudRect.height * 0.1f, fontSize, BLACK );

    PauseButton.draw();
}