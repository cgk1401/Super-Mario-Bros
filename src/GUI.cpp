#include "../headers/GUI.h"
#include "../headers/Global.h"
#include "../headers/MenuState.h"
#include "../headers/PauseState.h"
#include <string>
using namespace std;

GUI::GUI(){
    coins = 0;
    time = 300.5;
    score = 0;
    map_level = 1;
    lives = 3;
    hudRect = Rectangle{ 0, 0,  screenWidth, 0.2f * screenHeight };
    font = LoadFont("../assets/font/PolygonParty.ttf");
    fontSize = 40;
    PauseButton = new Button("../assets/GUI/Pause Button.png", screenWidth * 0.03f, screenHeight * 0.02f, 75, 75, "", WHITE, 40);
    //mario = Mario(50, 50);

}
GUI::~GUI() {
    
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
    this->map_level = m;
}
void GUI::setTime(int t){
    this->time = t;
}

bool GUI::PauseButton_IsPressed(){
    return PauseButton->IsClicked();
}
void GUI::update(Game& game){
    PauseButton->update();
    if(time > 0) time -= 2 * GetFrameTime();
    else {
        time = 0;
        //Time out => Display this menu: Restart + Menu
    }
    
}
void GUI::draw(){
    Color textColor = WHITE;
    DrawTextEx(font, TextFormat("Score\n %d", score), { hudRect.x + hudRect.width * 0.22f, hudRect.y + hudRect.height * 0.1f }, fontSize, 5, textColor);
    DrawTextEx(font, TextFormat("Coins\n %d", coins), { hudRect.x + hudRect.width * 0.37f, hudRect.y + hudRect.height * 0.1f }, fontSize, 5, textColor);
    DrawTextEx(font, TextFormat("Map\n %d", map_level), { hudRect.x + hudRect.width * 0.54f, hudRect.y + hudRect.height * 0.1f }, fontSize, 5, textColor);
    DrawTextEx(font, TextFormat("Time\n %d", (int)time), { hudRect.x + hudRect.width * 0.67f, hudRect.y + hudRect.height * 0.1f }, fontSize, 5, textColor);
    DrawTextEx(font, TextFormat("Lives\n %d", lives), {hudRect.x + hudRect.width * 0.82f, hudRect.y + hudRect.height * 0.1f}, fontSize, 5, textColor );

    PauseButton->draw();
}