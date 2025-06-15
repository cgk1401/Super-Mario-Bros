#include "../headers/Game.h"
#include <iostream>
using namespace std;

Game* Game::instance = nullptr;

Game* Game::getInstance(){
     if (!instance) {
         instance = new Game();
     }
    return instance;
}

//Constructor
Game::Game(){
    // cout << "Game: Constructor is called" << endl;
    init();    
    
}

//Destructor
Game::~Game(){
    // cout << "Game: Destructor is called" << endl;
    delete currentState;
    CloseWindow();
}

void Game::run(){
    
    while(!WindowShouldClose()){
        //Xử lí event
        currentState->update(*this);

        BeginDrawing();
            ClearBackground(SKYBLUE);
            //Vẽ 
            currentState->render();
        EndDrawing();
    }
    
}

void Game::init(){
    currentState = nullptr;
}

void Game::changeState(GameState* newState){
    if (currentState) delete currentState;
    currentState = newState;
 }