#include "raylib.h"
#include "../headers/Game.h"
#include "../headers/MenuState.h"
#include "../headers/Global.h"


int main() {

    InitWindow(screenWidth, screenHeight, "My Mario Game - Group 10");
    SetTargetFPS(60);
    //Access the Game instance
    Singleton<Game>::getInstance().clear();
    Singleton<Game>::getInstance().addState(new MenuState()); //Begin with main menu
    Singleton<Game>::getInstance().run();
   

    return 0;
}