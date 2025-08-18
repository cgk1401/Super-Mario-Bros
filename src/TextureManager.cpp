#include "../headers/TextureManager.h"
#include <string>


TextureManager::TextureManager(){
    texture.emplace(TextureType::MARIO, LoadTexture("../assets/Mario/Mario & Luigi.png"));
    texture.emplace(TextureType::MARIOINVINCIBILITY, LoadTexture("../assets/Mario/mario_luigi_4.png"));
    texture.emplace(TextureType::ENEMY, LoadTexture("../assets/Enemy/Enemies_Bosses.png"));
    texture.emplace(TextureType::BUTTON, LoadTexture("../assets/GUI/Button.png"));
    texture.emplace(TextureType::ITEM, LoadTexture("../assets/Item/Items Objects and NPCs.png"));
    texture.emplace(TextureType::LUIGI, LoadTexture("../assets/GUI/Luigi.png"));
    texture.emplace(TextureType::TILESET, LoadTexture("../assets/Map/tileset_gutter64x64.png"));
    texture.emplace(TextureType::BUTTONPANEL, LoadTexture("../Assets/Gui/buttonPanel.png"));
    texture.emplace(TextureType::AUDIOPANEL, LoadTexture("../Assets/Gui/volume slider.png"));
    texture.emplace(TextureType::BACKGROUND_1, LoadTexture("../assets/GUI/Menu Background.png"));
    texture.emplace(TextureType::BACKGROUND_2, LoadTexture("../assets/GUI/option_background.png"));


    font.emplace(MyFontType::DANGER, LoadFont("../assets/font/danger.ttf"));
    font.emplace(MyFontType::KNIGHT_WARRIOR, LoadFont("../assets/font/knightwarrior.otf"));
    font.emplace(MyFontType::POLYGON_PARTY, LoadFont("../assets/font/PolygonParty.ttf"));

}

 TextureManager::~TextureManager(){
    for(auto& it: texture){
        UnloadTexture(it.second);
    }
    texture.clear();
 }


Texture2D& TextureManager::load(TextureType type){
    /*if (texture.find(type) == texture.end()) {
       TraceLog(LOG_ERROR, "INVALID TYPE");
       return Te{};
    }*/
    return texture[type];
}

Font& TextureManager::load(MyFontType type){
    if (font.find(type) == font.end()) {
       TraceLog(LOG_ERROR, "INVALID TYPE");
       return font[MyFontType::DANGER];
    }
    return font[type];
}


