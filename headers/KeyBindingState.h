#pragma once
#include <unordered_map>
#include "GameState.h"
#include <vector>
#include <raylib.h>
struct Controls
{
    int moveLeft = KEY_LEFT;
    int moveRight = KEY_RIGHT;
    int jump = KEY_UP;
    int crouch = KEY_DOWN;
};
static std::unordered_map<int, std::string> keyNames = {
    // Letters
    {KEY_A, "A"},
    {KEY_B, "B"},
    {KEY_C, "C"},
    {KEY_D, "D"},
    {KEY_E, "E"},
    {KEY_F, "F"},
    {KEY_G, "G"},
    {KEY_H, "H"},
    {KEY_I, "I"},
    {KEY_J, "J"},
    {KEY_K, "K"},
    {KEY_L, "L"},
    {KEY_M, "M"},
    {KEY_N, "N"},
    {KEY_O, "O"},
    {KEY_P, "P"},
    {KEY_Q, "Q"},
    {KEY_R, "R"},
    {KEY_S, "S"},
    {KEY_T, "T"},
    {KEY_U, "U"},
    {KEY_V, "V"},
    {KEY_W, "W"},
    {KEY_X, "X"},
    {KEY_Y, "Y"},
    {KEY_Z, "Z"},

    // Numbers
    {KEY_ZERO, "0"},
    {KEY_ONE, "1"},
    {KEY_TWO, "2"},
    {KEY_THREE, "3"},
    {KEY_FOUR, "4"},
    {KEY_FIVE, "5"},
    {KEY_SIX, "6"},
    {KEY_SEVEN, "7"},
    {KEY_EIGHT, "8"},
    {KEY_NINE, "9"},

    // Function keys
    {KEY_F1, "F1"},
    {KEY_F2, "F2"},
    {KEY_F3, "F3"},
    {KEY_F4, "F4"},
    {KEY_F5, "F5"},
    {KEY_F6, "F6"},
    {KEY_F7, "F7"},
    {KEY_F8, "F8"},
    {KEY_F9, "F9"},
    {KEY_F10, "F10"},
    {KEY_F11, "F11"},
    {KEY_F12, "F12"},

    // Control keys
    {KEY_SPACE, "Space"},
    {KEY_ESCAPE, "Escape"},
    {KEY_ENTER, "Enter"},
    {KEY_TAB, "Tab"},
    {KEY_BACKSPACE, "Backspace"},
    {KEY_LEFT, "Left Arrow"},
    {KEY_RIGHT, "Right Arrow"},
    {KEY_UP, "Up Arrow"},
    {KEY_DOWN, "Down Arrow"},
    {KEY_LEFT_SHIFT, "Left Shift"},
    {KEY_RIGHT_SHIFT, "Right Shift"},
    {KEY_LEFT_CONTROL, "Left Ctrl"},
    {KEY_RIGHT_CONTROL, "Right Ctrl"},
    {KEY_LEFT_ALT, "Left Alt"},
    {KEY_RIGHT_ALT, "Right Alt"},
    {KEY_CAPS_LOCK, "Caps Lock"},

    // Navigation
    {KEY_HOME, "Home"},
    {KEY_END, "End"},
    {KEY_INSERT, "Insert"},
    {KEY_DELETE, "Delete"},
    {KEY_PAGE_UP, "Page Up"},
    {KEY_PAGE_DOWN, "Page Down"},
};

inline std::string GetKeyNameCustom(int key)
{
    if (keyNames.count(key))
        return keyNames[key];
    return "Unknown";
}
class KeyBindingState : public GameState
{
public:
    static Controls controls;

    KeyBindingState();
    void handleInput() override;
    void update(float dt) override;
    void render() override;
    bool allowUpdateBelow() { return false; }
    void setControlKey(int index, int newKey);
private:
    int selectedIndex;
    bool waitingForKey;
    char keyPress;
    Texture2D texture;
    Font FONT;
    std::vector<Rectangle> buttons;
    Button *backButton;
    Rectangle audioButton;

};
