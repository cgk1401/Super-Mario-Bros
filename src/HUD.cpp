#include "../headers/HUD.h"
#include "../headers/Global.h"
#include "../headers/MenuState.h"
#include "../headers/PauseState.h"
#include <string>
using namespace std;

HUD::HUD(pair<int, int> level){
    coins = 0;
    time = 400.5;
    score = 0;
    map_level = level;
    lives = 3;
    hudRect = Rectangle{ 0, 0,  screenWidth, 0.2f * screenHeight };
    font = LoadFont("../assets/font/PolygonParty.ttf");
    fontSize = 40;
    
    //mario = Mario(50, 50);

}
HUD::~HUD() {
    
}
void HUD::setScore(int s){
    this->score = s;
}

void HUD::setCoins(int c){
    this->coins = c;
}
void HUD::setLives(int l){
    this->lives = l;
}
void HUD::setMapLevel(pair<int, int> m){
    this->map_level = m;
}
void HUD::setTime(int t){
    this->time = t;
}
int HUD::getLives(){
    return lives;
}
int HUD::getTime(){
    return time;
}
int HUD::getScore(){
    return score;
}
int HUD::getCoin() {
    return coins;
}

void HUD::generateTimeToCoins(){
    if(time <= 0 ) {
        time = 0;
        return;
    }
    time--;
    score += 100 ;
    if((int)time % 5 == 0) Singleton<SoundManager>::getInstance().play(SoundType::BEEP);
}

void HUD::onNotify(const EventType& event, void* data){
    if (event == EventType::ON_DEATH) {
        lives--;
        score = 0;
        time = 400.5f;
    }
    else if(event == EventType::FINISH_LEVEL){
        time = 400.5f;
    }
   map<EventType, EventInfo> eventMap = Singleton<EventDataBase>::getInstance().getMap();
    auto it = eventMap.find(event);
    if(it == eventMap.end()) return;
    score += it->second.score;
    
    if(event == EventType::COIN_COLLECT){
        coins++;
    }
}
void HUD::update(float dt){

    
    if(time > 0) time -= 2.5 * dt;
    else {
        time = 0;
        //Time out => Display this menu: Restart + Menu
    }
    
}
void HUD::draw(){
    Color textColor = WHITE;
    DrawTextEx(font, TextFormat("Score\n %d", score), { hudRect.x + hudRect.width * 0.22f, hudRect.y + hudRect.height * 0.1f }, fontSize, 5, textColor);
    DrawTextEx(font, TextFormat("Coins\n %d", coins), { hudRect.x + hudRect.width * 0.37f, hudRect.y + hudRect.height * 0.1f }, fontSize, 5, textColor);
    DrawTextEx(font, TextFormat(" Map\n%d - %d", map_level.first, map_level.second), { hudRect.x + hudRect.width * 0.52f, hudRect.y + hudRect.height * 0.1f }, fontSize, 5, textColor);
    DrawTextEx(font, TextFormat("Time\n %d", (int)time), { hudRect.x + hudRect.width * 0.67f, hudRect.y + hudRect.height * 0.1f }, fontSize, 5, textColor);
    DrawTextEx(font, TextFormat("Lives\n %d", lives), {hudRect.x + hudRect.width * 0.82f, hudRect.y + hudRect.height * 0.1f}, fontSize, 5, textColor );

    
}