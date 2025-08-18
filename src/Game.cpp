#include "Game.h"
#include "SoundManager.h"
#include "MenuState.h"
#include "PlayState.h"
#include <iostream>
using namespace std;

Game::Game(){
    InitAudioDevice();
    InitWindow(screenWidth, screenHeight, "My Mario Game - Group 10");
    SetTargetFPS(60);
}

Game::~Game(){
    for (auto& s : stateStack) delete s;
    CloseAudioDevice();
    CloseWindow();

}

void Game::run(){
    addState(new MenuState());
    while(!WindowShouldClose()){
        float deltatime = GetFrameTime();
        for (int i = stateStack.size() - 1; i >= 0; i--) {
            stateStack[i]->handleInput();
            if (i > stateStack.size() - 1) break;
             stateStack[i]->update(deltatime);
             if (i > stateStack.size() - 1) break;
             if (!stateStack[i]->allowUpdateBelow()) break;
        }
    
        BeginDrawing();
            Color bgColor = Color{92, 148, 252};
            ClearBackground(bgColor);
            for (int i = 0; i < stateStack.size(); i++) {
                stateStack[i]->render();
            }
        EndDrawing();

        if(WindowShouldClose()){
            for(auto& state: stateStack){
                if(auto playstate = dynamic_cast<PlayState*>(state)){
                    playstate->saveGame("savegame.json");
                }
            }
        }
    }
    
}

void Game::addState(GameState* newGameState) {
    stateStack.push_back(newGameState);
}
void Game::pop() {
    if (stateStack.size() > 1) {
        delete stateStack.back(); 
        stateStack.pop_back();
    }
}

void Game::changeState(GameState* newState) {
    clear();
    addState(newState);
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

GameState* Game::getFirstState() {
    return stateStack.back();
}
