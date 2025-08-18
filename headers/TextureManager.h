#pragma once
#include <raylib.h>
#include <unordered_map>
using namespace std;

template <typename T>
class Singleton;

enum class TextureType {
    MARIO,
    MARIOINVINCIBILITY,
    ENEMY,
    TILESET,
    ITEM,
    BUTTON,
    LUIGI,
    BUTTONPANEL,
    AUDIOPANEL,
    BACKGROUND_1,
    BACKGROUND_2,
};

enum class MyFontType {
    DANGER,
    KNIGHT_WARRIOR,
    POLYGON_PARTY,
};
class TextureManager{
    template <typename T>
    friend class Singleton;
private:
    unordered_map<TextureType, Texture2D> texture;
    unordered_map<MyFontType, Font> font;
    TextureManager();
    ~TextureManager();
public:
    Texture2D& load(TextureType type);
    Font& load(MyFontType type);
};