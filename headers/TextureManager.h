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
};

class TextureManager{
    template <typename T>
    friend class Singleton;
private:
    unordered_map<TextureType, Texture2D> texture;
    TextureManager();
    ~TextureManager();
public:
    Texture2D& load(TextureType type);
};