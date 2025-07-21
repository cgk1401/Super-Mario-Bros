#pragma once
#include "../headers/GameState.h"
#include "../headers/Global.h"
#include "../headers/Button.h"
using namespace std;

class CharacterSelection : public GameState {
private:
    vector<Button*> buttons;
    Font font;
    Texture2D background;
    vector <Texture2D> characters;
    Texture2D* selectCharacter;
public:
    CharacterSelection();
    ~CharacterSelection();

    void update(float deltatime) override;
    void render() override;

    Texture2D* getSelectedCharacter(){return  selectCharacter;}
};