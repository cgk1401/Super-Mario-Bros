#include "../headers/Game.h"
#include "../headers/SoundManager.h"
#include <iostream>
using namespace std;

//Constructor
Game::Game(){
    // cout << "Game: Constructor is called" << endl;
    init();   
    
}

//Destructor
Game::~Game(){
    // cout << "Game: Destructor is called" << endl;
    for (auto& s : stateStack) delete s;
    CloseAudioDevice();
    CloseWindow();

}

void Game::run(){

    while(!WindowShouldClose()){
        //Xử lí event
        float deltatime = GetFrameTime();
        cout << stateStack.size() << endl;
        for (int i = stateStack.size() - 1; i >= 0; i--) {
            
             stateStack[i]->update(deltatime);
             if (i > stateStack.size() - 1) break;
             if (!stateStack[i]->allowUpdateBelow()) break;
        }
    
        BeginDrawing();
            ClearBackground(Color{92, 148, 252});
            //Vẽ 
            
            for (int i = 0; i < stateStack.size(); i++) {
                stateStack[i]->render();
            }
           
        EndDrawing();
    }
    
}

void Game::init(){
    InitAudioDevice();
}

//void Game::changeState(GameState* newState){
//    if (currentState) delete currentState;
//    currentState = newState;
// }

void Game::addState(GameState* newGameState) {
    stateStack.push_back(newGameState);
}
void Game::pop() {
    if (!stateStack.empty()) {
        delete stateStack.back();  // FREE
        stateStack.pop_back();
    }
}
void Game::replaceState(GameState* newState) {
    pop();
    addState(newState);
}

void Game::clear() {
    for (auto& s : stateStack) delete s;
    stateStack.clear();
}

int Game::getStateCount() {
    return stateStack.size();
}

vector<GameState*>& Game::getstateStack(){
    return this->stateStack;
}
