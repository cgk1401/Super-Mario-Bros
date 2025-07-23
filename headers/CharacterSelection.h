#pragma once
#include "../headers/GameState.h"
#include "../headers/Global.h"
#include "../headers/Button.h"
using namespace std;

class CharacterSelection : public GameState {
private:
    Button* backButton;
  
    Font font;
    Texture2D background;
    vector <Texture2D> characters;
    vector<Button*> characterChoices;
    Texture2D* selectCharacter;
public:
    CharacterSelection();
    ~CharacterSelection();

    void update(float deltatime) override;
    void render() override;
    bool allowUpdateBelow() override { return false; }
    Texture2D* getSelectedCharacter(){return  selectCharacter;}
};