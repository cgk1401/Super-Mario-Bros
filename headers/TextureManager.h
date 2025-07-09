#pragma once
#include <raylib.h>
#include <unordered_map>
using namespace std;

enum class TextureType{
    MARIO,
    ENEMY,
    TILESET,
    ITEM,
    BUTTON
};

class TextureManager{
private:
    unordered_map<TextureType, Texture2D> texture;
    static TextureManager* instance;
    TextureManager();
    ~TextureManager();
public:
    static TextureManager& get(){
        //TraceLog(LOG_INFO, "Load texture");
        if(!instance)
            instance = new TextureManager;
        return *instance;
    }

    Texture2D& load(TextureType type);
    
};