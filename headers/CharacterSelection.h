#pragma once
#include "../headers/GameState.h"
#include "../headers/Global.h"
#include "../headers/Button.h"
using namespace std;

class CharacterSelection : public GameState {
private:
    Button* backButton;
    Button* play_button;

    Font font;
    Texture2D background;
    vector <Texture2D> characters;
    vector<Button*> characterChoices;
    Texture2D* selectCharacter;

    Timer time;
    float speed = 11.8f;
    // bool startLaunching = false;
    // float scale = 1;
public:
    CharacterSelection();
    ~CharacterSelection();

    void update(float deltatime) override;
    void render() override;
    bool allowUpdateBelow() override { return false; }
    Texture2D* getSelectedCharacter(){return  selectCharacter;}
};