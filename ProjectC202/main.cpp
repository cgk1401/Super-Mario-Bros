#include "raylib.h"
#include "Game.h"
#include "MenuState.h"
#include "Global.h"

int main() {

    InitWindow(screenWidth, screenHeight, "My Mario Game - Group 10");
    SetTargetFPS(120);
    //Access the Game instance
    Game* game = Game::getInstance();
    game->changeState(new MenuState()); //Begin with main menu
    game->run();

    return 0;
}